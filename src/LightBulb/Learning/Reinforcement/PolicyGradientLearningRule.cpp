// Includes
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningResult.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"

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
		initialize(static_cast<PolicyGradientLearningRuleOptions&>(*options.get()));
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_)
		: AbstractReinforcementLearningRule(options_)
	{
		initialize(*options_);
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule()
		: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions())
	{
		initialize(static_cast<PolicyGradientLearningRuleOptions&>(*options.get()));
	}

	PolicyGradientLearningRule::~PolicyGradientLearningRule() = default;

	void PolicyGradientLearningRule::initialize(PolicyGradientLearningRuleOptions& options)
	{
		recordStart = 0;
		nextRecordIndex = 0;

		gradientCalculation.reset(new Backpropagation());
		gradientDescentAlgorithm.reset(new RMSPropLearningRate(options.rmsPropLearningRateOptions));

		valueFunctionGradientCalculation.reset(new Backpropagation());
		valueFunctionGradientDescentAlgorithm.reset(new RMSPropLearningRate(options.valueRmsPropLearningRateOptions));
	}

	void PolicyGradientLearningRule::initializeLearningAlgoritm()
	{
		gradientDescentAlgorithm->initialize(getOptions().environment->getNeuralNetwork().getNetworkTopology());
		gradientCalculation->initWithExternalGradient(getOptions().environment->getNeuralNetwork().getNetworkTopology());
		stateRecord.resize(getOptions().episodeSize);
		gradientRecord.resize(getOptions().episodeSize);
		rewardRecord.resize(getOptions().episodeSize);
		isTerminalStateRecord.resize(getOptions().episodeSize);

		lastOutput.resize(getOptions().environment->getNeuralNetwork().getNetworkTopology().getOutputSize());
		if (getOptions().valueFunctionAsBase)
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

	void PolicyGradientLearningRule::recordStep(AbstractNetworkTopology& networkTopology, Scalar<> reward)
	{
		Vector<> errorVector;
		getErrorVector(networkTopology, errorVector);
		
		stateRecord[nextRecordIndex] = getOptions().environment->getLastInput();

		rewardRecord[nextRecordIndex] = reward;

		getOptions().environment->isTerminalState(isTerminalStateRecord[nextRecordIndex]);
		
		if (gradientRecord[nextRecordIndex].empty())
			gradientRecord[nextRecordIndex] = networkTopology.getAllWeights();

		for (int i = 0; i < gradientRecord[nextRecordIndex].size(); i++)
			gradientRecord[nextRecordIndex][i].getEigenValueForEditing().setZero();
		
		gradientCalculation->calcGradient(networkTopology, errorVector, gradientRecord[nextRecordIndex], &getOptions().environment->getLastInput());

		nextRecordIndex++;
		nextRecordIndex %= getOptions().episodeSize;
	}

	void PolicyGradientLearningRule::getErrorVector(AbstractNetworkTopology& networkTopology, Vector<>& errorVector)
	{
		networkTopology.getOutput(lastOutput);

		errorVector.getEigenValueForEditing().resize(lastOutput.size());
		for (int i = 0; i < lastOutput.size(); i++)
		{
			errorVector.getEigenValueForEditing()(i) = getOptions().environment->getLastBooleanOutput().getEigenValue()(i) - lastOutput[i];//-2 * std::signbit(getOptions()->environment->getLastBooleanOutput()[i] - lastOutput[i]) + 1;
		}
		errorSum += errorVector.getEigenValueForEditing().cwiseAbs().sum();
		errorSteps++;
	}

	void PolicyGradientLearningRule::initializeTry()
	{
		//resilientLearningRateHelper->initialize(*getOptions()->environment->getNeuralNetwork());
		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->initializeForLearning();

		recordStart = 0;
		nextRecordIndex = 0;

		if (getOptions().valueFunctionAsBase)
		{
			valueFunctionNetwork->getNetworkTopology().randomizeDependingOnLayerSize(*randomGenerator.get());
		}
	}

	
	std::string PolicyGradientLearningRule::getName()
	{
		return "PolicyGradientLearningRule";
	}

	std::vector<std::string> PolicyGradientLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_ERROR_AVG);
		if (getOptions().valueFunctionAsBase)
			labels.push_back(DATA_SET_VALUE_ERROR_AVG);
		return labels;
	}


	void PolicyGradientLearningRule::doIteration()
	{
		double totalReward = 0;
		errorSum = 0;
		valueErrorSum = 0;
		errorSteps = 0;
		valueErrorSteps = 0;
		AbstractNetworkTopology& networkTopology = getOptions().environment->getNeuralNetwork().getNetworkTopology();
		gradient.clear();
		if (getOptions().valueFunctionAsBase)
			valueFunctionGradientCalculation->initGradient(valueFunctionNetwork->getNetworkTopology());

		do
		{
			Scalar<> reward;
			getOptions().environment->doSimulationStep(reward);

			recordStep(networkTopology, reward);

			totalReward += reward.getEigenValue();
		} while (nextRecordIndex != recordStart);
		
		learningState->addData(DATA_SET_REWARD, totalReward);

		learningState->addData(DATA_SET_ERROR_AVG, errorSum / errorSteps);
		if (getOptions().valueFunctionAsBase)
			learningState->addData(DATA_SET_VALUE_ERROR_AVG, valueErrorSum / valueErrorSteps);

		computeGradients();
		addGradients(networkTopology);

		// Continue with the next generation
		learningState->iterations++;

		if (learningState->iterations % getOptions().ratingInterval == 0)
		{
			getOptions().environment->setStochasticActionDecision(false);
			getOptions().environment->rate();
			getOptions().environment->setStochasticActionDecision(true);
		}
	}


	void PolicyGradientLearningRule::addGradients(AbstractNetworkTopology& networkTopology)
	{
		for (int l = gradient.size() - 1; l >= 0; l--)
		{
			gradientDescentAlgorithm->adjustWeights(networkTopology, networkTopology.getAllWeights()[l], l + 1, gradient[l]);
		}

		if (getOptions().valueFunctionAsBase)
		{
			for (int l = valueFunctionGradientCalculation->getGradient().size() - 1; l >= 0; l--)
			{
				valueFunctionGradientDescentAlgorithm->adjustWeights(valueFunctionNetwork->getNetworkTopology(), valueFunctionNetwork->getNetworkTopology().getAllWeights()[l], l + 1, valueFunctionGradientCalculation->getGradient().at(l));
			}
		}
	}

	const PolicyGradientLearningRuleOptions& PolicyGradientLearningRule::getOptions() const
	{
		return static_cast<PolicyGradientLearningRuleOptions&>(*options.get());
	}

	void PolicyGradientLearningRule::doCalculationAfterLearningProcess()
	{
	}

	void PolicyGradientLearningRule::computeGradients()
	{
		int lastRelevantIndex = -1;
		int i = nextRecordIndex - 1;
		do
		{
			if (i < 0)
				i = getOptions().episodeSize - 1;

			if (lastRelevantIndex == -1 && isTerminalStateRecord[i].getEigenValue())
				lastRelevantIndex = i;
			if (lastRelevantIndex != -1) 
			{
				if (!isTerminalStateRecord[i].getEigenValue())
					rewardRecord[i].getEigenValueForEditing() += rewardRecord[(i + 1) % getOptions().episodeSize].getEigenValue() * 0.99;
			}
			i--;
		} while (i != recordStart - 1);

		if (lastRelevantIndex == -1)
			throw std::logic_error("There has been no terminal states in the last " + std::to_string(getOptions().episodeSize) + " steps.");

	/*	rewards = rewards.array() - rewards.mean();
		double stddev = std::sqrt(rewards.cwiseAbs2().sum() / stepsSinceLastReward);
		rewards = rewards.array() / stddev;*/

		for (i = recordStart; i != (lastRelevantIndex + 1) % getOptions().episodeSize; i++, i %= getOptions().episodeSize)
		{
			/*if (getOptions().valueFunctionAsBase)
			{
				std::vector<double> output(1);
				valueFunctionNetwork->calculate(stateRecord[i], output, TopologicalOrder());

				Vector<> errorVector(1);
				errorVector.getEigenValueForEditing()(0) = rewards(i) - output[0];
				valueFunctionGradientCalculation->calcGradient(valueFunctionNetwork->getNetworkTopology(), errorVector);
				valueErrorSum += abs(errorVector.getEigenValue()(0));
				valueErrorSteps++;

				rewards(i) -= output[0];
			}*/
			
			if (gradient.empty())
			{
				for (int j = 0; j < gradientRecord[i].size(); j++)
					gradientRecord[i][j].getEigenValueForEditing().noalias() = gradientRecord[i][j].getEigenValue() * rewardRecord[i].getEigenValue();
				gradient = gradientRecord[i];
			}
			else
			{
				for (int j = 0; j < gradientRecord[i].size(); j++)
					gradient[j].getEigenValueForEditing().noalias() = gradient[j].getEigenValue() + gradientRecord[i][j].getEigenValue() * rewardRecord[i].getEigenValue();
			}
		}

		recordStart = (lastRelevantIndex + 1) % getOptions().episodeSize;
	}


}
