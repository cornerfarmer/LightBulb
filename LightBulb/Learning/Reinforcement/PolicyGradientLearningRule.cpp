// Includes
#include "Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <Learning/Evolution/EvolutionLearningResult.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include "AbstractReinforcementWorld.hpp"
#include "NeuronDescription/NeuronDescription.hpp"
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "Function/InputFunction/WeightedSumFunction.hpp"
#include "Function/ActivationFunction/RectifierFunction.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"

namespace LightBulb
{
	AbstractLearningResult* PolicyGradientLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();

		return learningResult;
	}


	PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions& options_)
		: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions(options_))
	{
		initialize();
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_)
		: AbstractReinforcementLearningRule(options_)
	{
		initialize();
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule()
		: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions())
	{
		initialize();
	}

	void PolicyGradientLearningRule::initialize()
	{
		gradientCalculation.reset(new Backpropagation());
		gradientDescentAlgorithm.reset(new RMSPropLearningRate(getOptions()->rmsPropLearningRateOptions));

		valueFunctionGradientCalculation.reset(new Backpropagation());
		valueFunctionGradientDescentAlgorithm.reset(new RMSPropLearningRate(getOptions()->valueRmsPropLearningRateOptions));
	}

	void PolicyGradientLearningRule::initializeLearningAlgoritm()
	{
		gradientDescentAlgorithm->initialize(getOptions()->world->getNeuralNetwork()->getNetworkTopology());
		errorVectorRecord.resize(1000);
		netInputRecord.resize(1000);
		activationRecord.resize(1000);
		lastOutput.resize(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getOutputSize());
		if (getOptions()->valueFunctionAsBase)
		{
			FeedForwardNetworkTopologyOptions options;
			options.enableShortcuts = false;
			options.useBiasNeuron = true;

			options.neuronsPerLayerCount.push_back(6);
			options.neuronsPerLayerCount.push_back(256);
			options.neuronsPerLayerCount.push_back(1);

			options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
			
			valueFunctionNetwork.reset(new NeuralNetwork(new FeedForwardNetworkTopology(options)));
			valueFunctionGradientDescentAlgorithm->initialize(valueFunctionNetwork->getNetworkTopology());
		}
	}

	void PolicyGradientLearningRule::recordStep(AbstractNetworkTopology* networkTopology)
	{
		getErrorVector(networkTopology, errorVectorRecord[stepsSinceLastReward]);

		netInputRecord[stepsSinceLastReward] = *networkTopology->getAllNetInputs();

		networkTopology->getActivationsCopy(activationRecord[stepsSinceLastReward]);
	}

	void PolicyGradientLearningRule::getErrorVector(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector)
	{
		networkTopology->getOutput(lastOutput);

		errorVector.resize(lastOutput.size());
		for (int i = 0; i < lastOutput.size(); i++)
		{
			errorVector(i) = getOptions()->world->getLastBooleanOutput()->at(i) - lastOutput[i];//-2 * std::signbit(getOptions()->world->getLastBooleanOutput()[i] - lastOutput[i]) + 1;
		}
		errorSum += errorVector.cwiseAbs().sum();
		errorSteps++;
	}

	void PolicyGradientLearningRule::initializeTry()
	{
		//resilientLearningRateHelper->initialize(*getOptions()->world->getNeuralNetwork());
		getOptions()->world->setLearningState(learningState.get());
		getOptions()->world->initializeForLearning();

		stepsSinceLastReward = 0;

		if (getOptions()->valueFunctionAsBase)
		{
			valueFunctionNetwork->getNetworkTopology()->randomizeDependingOnLayerSize(randomGenerator.get());
		}
	}

	
	std::string PolicyGradientLearningRule::getName()
	{
		return "PolicyGradientLearningRule";
	}

	std::vector<std::string> PolicyGradientLearningRule::getDataSetLabels()
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_ERROR_AVG);
		if (getOptions()->valueFunctionAsBase)
			labels.push_back(DATA_SET_VALUE_ERROR_AVG);
		return labels;
	}


	bool PolicyGradientLearningRule::doIteration()
	{
		int rewardCounter = 0;
		double totalReward = 0;
		errorSum = 0;
		valueErrorSum = 0;
		errorSteps = 0;
		valueErrorSteps = 0;
		AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();
		gradientCalculation->initGradient(networkTopology);
		if (getOptions()->valueFunctionAsBase)
			valueFunctionGradientCalculation->initGradient(valueFunctionNetwork->getNetworkTopology());

		while (rewardCounter < getOptions()->episodeSize)
		{
			double reward = getOptions()->world->doSimulationStep();

			recordStep(networkTopology);

			stepsSinceLastReward++;

			if (getOptions()->world->isTerminalState())
			{
				totalReward += reward;

				computeGradients(networkTopology, stepsSinceLastReward, reward);
				stepsSinceLastReward = 0;
				rewardCounter++;
			}
		}

		learningState->addData(DATA_SET_REWARD, totalReward);

		learningState->addData(DATA_SET_ERROR_AVG, errorSum / errorSteps);
		if (getOptions()->valueFunctionAsBase)
			learningState->addData(DATA_SET_VALUE_ERROR_AVG, valueErrorSum / valueErrorSteps);

		addGradients(networkTopology);

		// Continue with the next generation
		learningState->iterations++;

		if (learningState->iterations % getOptions()->ratingInterval == 0)
			getOptions()->world->rateKI();

		return true;
	}


	void PolicyGradientLearningRule::addGradients(AbstractNetworkTopology* networkTopology)
	{
		for (int l = gradientCalculation->getGradient()->size() - 1; l >= 0; l--)
		{
			Eigen::MatrixXd newWeights = networkTopology->getAfferentWeightsPerLayer(l + 1) + gradientDescentAlgorithm->calcDeltaWeight(networkTopology, l + 1, gradientCalculation->getGradient()->at(l));
			networkTopology->setAfferentWeightsPerLayer(l + 1, newWeights);
		}

		if (getOptions()->valueFunctionAsBase)
		{
			for (int l = valueFunctionGradientCalculation->getGradient()->size() - 1; l >= 0; l--)
			{
				Eigen::MatrixXd newWeights = valueFunctionNetwork->getNetworkTopology()->getAfferentWeightsPerLayer(l + 1) + valueFunctionGradientDescentAlgorithm->calcDeltaWeight(valueFunctionNetwork->getNetworkTopology(), l + 1, valueFunctionGradientCalculation->getGradient()->at(l));
				valueFunctionNetwork->getNetworkTopology()->setAfferentWeightsPerLayer(l + 1, newWeights);
			}
		}
	}

	PolicyGradientLearningRuleOptions* PolicyGradientLearningRule::getOptions()
	{
		return static_cast<PolicyGradientLearningRuleOptions*>(options.get());
	}

	void PolicyGradientLearningRule::doCalculationAfterLearningProcess()
	{
	}

	void PolicyGradientLearningRule::computeGradients(AbstractNetworkTopology* networkTopology, int stepsSinceLastReward, double reward)
	{
		Eigen::VectorXd rewards(stepsSinceLastReward);
		rewards(stepsSinceLastReward - 1) = reward;
		for (int i = stepsSinceLastReward - 2; i >= 0; i--)
		{
			rewards(i) = rewards(i + 1) * 0.99;
		}

	/*	rewards = rewards.array() - rewards.mean();
		double stddev = std::sqrt(rewards.cwiseAbs2().sum() / stepsSinceLastReward);
		rewards = rewards.array() / stddev;*/

		for (int i = 0; i < stepsSinceLastReward; i++)
		{
			if (getOptions()->valueFunctionAsBase)
			{
				std::vector<double> output(1);
				std::vector<double> input(activationRecord[i][0].data(), activationRecord[i][0].data() + activationRecord[i][0].size());
				valueFunctionNetwork->calculate(input, output, TopologicalOrder());

				ErrorMap_t errorMap(1, Eigen::VectorXd(1));
				errorMap[0](0) = rewards(i) - output[0];
				valueFunctionGradientCalculation->calcGradient(valueFunctionNetwork->getNetworkTopology(), &errorMap);
				valueErrorSum += abs(errorMap[0](0));
				valueErrorSteps++;

				rewards(i) -= output[0];
			}
			errorVectorRecord[i] = rewards(i) * errorVectorRecord[i].array();
			computeGradientsForError(networkTopology, errorVectorRecord[i], netInputRecord[i], activationRecord[i]);

		}

	}

	void PolicyGradientLearningRule::computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorXd>& activations)
	{
		ErrorMap_t errorMap(1, errorVector);
		std::vector<Eigen::VectorBlock<Eigen::VectorXd>> tmpBlock;
		for (int j = 0; j < activations.size(); j++)
			tmpBlock.push_back(Eigen::VectorBlock<Eigen::VectorXd>(activations[j].derived(), 0, activations[j].size()));
		gradientCalculation->calcGradient(networkTopology, netInputs, tmpBlock, &errorMap);
	}

}
