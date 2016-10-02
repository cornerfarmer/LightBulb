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

		if (getOptions()->actorCritic)
		{
			getOptions()->criticOptions.world = getOptions()->world;
			getOptions()->criticOptions.alternativeTargetNetwork = new NeuralNetwork(new FeedForwardNetworkTopology(getOptions()->criticNetworkOptions));
			critic.reset(new DQNLearningRule(getOptions()->criticOptions));
		}
		getOptions()->world->setPolicyBasedLearning(true);

	
		GradientDescentLearningRuleOptions options(getOptions()->criticOptions.gradientDescentOptions);
		options.gradientDescentAlgorithm = new RMSPropLearningRate(getOptions()->rmsPropLearningRateOptions);
		options.teacher = critic->getTeacher();
		options.neuralNetwork = getOptions()->world->getNeuralNetwork();
		options.logger = NULL;
		gradientDescent.reset(new GradientDescentLearningRule(options));
	}

	void PolicyGradientLearningRule::initializeLearningAlgoritm()
	{
		critic->learningState = learningState;
		gradientDescentAlgorithm->initialize(getOptions()->world->getNeuralNetwork()->getNetworkTopology());
		errorVectorRecord.resize(1000);
		netInputRecord.resize(1000);
		activationRecord.resize(1000);
		lastOutput.resize(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getOutputSize());
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
	}

	void PolicyGradientLearningRule::initializeTry()
	{
		//resilientLearningRateHelper->initialize(*getOptions()->world->getNeuralNetwork());
		if (getOptions()->actorCritic)
		{
			critic->initializeTry();
		}
		getOptions()->world->setLearningState(learningState.get());
		getOptions()->world->initializeForLearning();

		stepsSinceLastReward = 0;
	}

	
	std::string PolicyGradientLearningRule::getName()
	{
		return "PolicyGradientLearningRule";
	}

	std::vector<std::string> PolicyGradientLearningRule::getDataSetLabels()
	{
		std::vector<std::string> labels1 = AbstractReinforcementLearningRule::getDataSetLabels();
		std::vector<std::string> labels2 = critic->getDataSetLabels();
		labels1.insert(labels1.end(), labels2.begin(), labels2.end());
		return labels1;
	}


	bool PolicyGradientLearningRule::doIteration()
	{
		int rewardCounter = 0;
		double totalReward = 0;
		AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();
		gradientCalculation->initGradient(networkTopology);

		while (rewardCounter < getOptions()->episodeSize)
		{
			double reward = getOptions()->world->doSimulationStep();
			if (getOptions()->actorCritic)
			{
				critic->registerSimulationStep(reward);
			}

			computeGradients(networkTopology, stepsSinceLastReward, reward);
			addGradients(networkTopology);
			rewardCounter++;
		}

		learningState->addData(DATA_SET_REWARD, totalReward);

		//

		// Continue with the next generation
		learningState->iterations++;

		if (learningState->iterations % getOptions()->ratingInterval == 0)
			getOptions()->world->rateKI();

		return true;
	}


	void PolicyGradientLearningRule::addGradients(AbstractNetworkTopology* networkTopology)
	{
		static std::vector<Eigen::MatrixXd> prevDeltaWeights(gradientCalculation->getGradient()->size());
		for (int l = gradientCalculation->getGradient()->size() - 1; l >= 0; l--)
		{
			Eigen::MatrixXd newWeights = networkTopology->getAfferentWeightsPerLayer(l + 1) + gradientDescentAlgorithm->calcDeltaWeight(networkTopology, l + 1, gradientCalculation->getGradient()->at(l));
			networkTopology->setAfferentWeightsPerLayer(l + 1, newWeights);
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
		Teacher* teacher = critic->getTeacher();
		TopologicalOrder order;
		if (teacher->getTeachingLessons()->size() > 0) {
			for (auto teachingLesson = teacher->getTeachingLessons()->begin(); teachingLesson != teacher->getTeachingLessons()->end(); teachingLesson++)
			{
				
				auto output = (*teachingLesson)->tryLesson(*getOptions()->world->getNeuralNetwork(), order).front();
				Eigen::VectorXd errorVector(output.size());


				int action = 0;
				for (int i = 0; i < 2; i++)
				{
					if ((*teachingLesson)->getTeachingInput(networkTopology->getOutputNeuronDescription()->getActivationFunction())->exists(0, i))
					{
						action = i;
						break;
					}
				}
				

				double q = critic->calculateActionValue((*teachingLesson)->getTeachingPattern()->front(), action);

				if (action == 1)
					errorVector[0] = 1 - output[0];
				else
					errorVector[0] = 0 - output[0];

				//q = std::max(-1.0, std::min(1.0, q));
				errorVector = q * errorVector;
				computeGradientsForError(networkTopology, errorVector);
			}
		}

	}

	void PolicyGradientLearningRule::computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector)
	{
		ErrorMap_t errorMap(1, errorVector);
		gradientCalculation->calcGradient(networkTopology, &errorMap);
	}

}
