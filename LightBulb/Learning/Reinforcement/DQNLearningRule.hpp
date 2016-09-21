#pragma once

#ifndef _DQNLEARNINGRULE_H_
#define _DQNLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include <Teaching/Teacher.hpp>
#include "Learning/Supervised/GradientDescentLearningRule.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

#define DATA_SET_TRAINING_ERROR "Training error"
#define DATA_SET_EPSILON "Epsilon"
#define DATA_SET_Q_VALUE "Q-Value"
#define DATA_SET_AVG_Q_VALUE "Avg. Q-Value"

	struct DQNLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{
		int minibatchSize;
		int replayMemorySize;
		int targetNetworkUpdateFrequency;
		double discountFactor;
		double initialExploration;
		double finalExploration;
		int finalExplorationFrame;
		int replayStartSize;
		bool replaceStoredTransitions;

		GradientDescentLearningRuleOptions gradientDescentOptions;

		RMSPropLearningRateOptions rmsPropOptions;
		DQNLearningRuleOptions()
		{
			minibatchSize = 32;
			replayMemorySize = 1000000;
			targetNetworkUpdateFrequency = 10000;
			discountFactor = 0.99;
			initialExploration = 1;
			finalExploration = 0.1;
			finalExplorationFrame = 1000000;
			replayStartSize = 50000;
			replaceStoredTransitions = true;

			gradientDescentOptions.maxIterationsPerTry = 1;
			gradientDescentOptions.maxTries = 1;
			gradientDescentOptions.changeWeightsBeforeLearning = false;
			gradientDescentOptions.offlineLearning = true;
			gradientDescentOptions.totalErrorGoal = -1;
			gradientDescentOptions.clipError = true;

			rmsPropOptions.learningRate = 0.00025;
		}
	};

	struct Transition
	{
		std::vector<double> state;
		std::vector<double> nextState;
		int action;
		double reward;
	};

	class DQNLearningRule : public AbstractReinforcementLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, DQNLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<DQNLearningRule>;
	private:
		int nextTransitionIndex;
		int waitUntilLearningStarts;
		double currentTotalError;
		double currentTotalReward;
		Teacher teacher;
		std::vector<Transition> transitions;
		std::unique_ptr<GradientDescentLearningRule> gradientDescent;
		std::unique_ptr<AbstractNeuralNetwork> steadyNetwork;
		double qAvgSum;
		void initialize();
		void storeTransition(AbstractNetworkTopology* networkTopology, double reward);
		void doSupervisedLearning();
		std::vector<Eigen::MatrixXd> checkGradient(Teacher* teacher, AbstractNetworkTopology* networkTopology);
	protected:
		bool doIteration() override;
		DQNLearningRuleOptions* getOptions() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		DQNLearningRule(DQNLearningRuleOptions& options_);
		DQNLearningRule(DQNLearningRuleOptions* options_);
		DQNLearningRule();
		// Executes the learning process
		void initializeTry() override;
		static std::string getName();
		std::vector<std::string> getDataSetLabels() override;
	};
}

#include "IO/DQNLearningRuleIO.hpp"


#endif
