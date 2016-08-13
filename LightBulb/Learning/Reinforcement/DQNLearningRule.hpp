#pragma once

#ifndef _DQNLEARNINGRULE_H_
#define _DQNLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include <Teaching/Teacher.hpp>
#include <Learning/ResilientLearningRateHelper.hpp>
#include <Learning/BackpropagationLearningRule.hpp>

// Library Includes
#include <vector>

// Forward declarations
class AbstractNetworkTopology;

#define DATA_SET_TRAINING_ERROR "Training error"

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

	BackpropagationLearningRuleOptions backpropagationOptions;
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
		
		backpropagationOptions.maxIterationsPerTry = 1;
		backpropagationOptions.maxTries = 1;
		backpropagationOptions.changeWeightsBeforeLearning = false;
		backpropagationOptions.resilientLearningRate = false;
		backpropagationOptions.flatSpotEliminationFac = 0;
		backpropagationOptions.offlineLearning = true;
		backpropagationOptions.totalErrorGoal = 0;
		backpropagationOptions.learningRate = 0.00025;
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
private:
	int nextTransitionIndex;
	int waitUntilLearningStarts;
	double currentTotalError;
	Teacher teacher;
	std::vector<Transition> transitions;
	std::unique_ptr<BackpropagationLearningRule> backpropagationLearningRule;
	std::unique_ptr<AbstractNeuralNetwork> steadyNetwork;
	void initialize();
	void storeTransition(AbstractNetworkTopology* networkTopology, double reward);
	void doSupervisedLearning();
	std::vector<Eigen::MatrixXd> checkGradient(Teacher* teacher, AbstractNetworkTopology* networkTopology);
protected:
	bool doIteration();
	DQNLearningRuleOptions* getOptions();
	AbstractLearningResult* getLearningResult();
public:
	DQNLearningRule(DQNLearningRuleOptions& options_);
	DQNLearningRule(DQNLearningRuleOptions* options_);
	DQNLearningRule();
	// Executes the learning process
	void initializeTry();
	static std::string getName();
	std::vector<std::string> getDataSetLabels();
};


#endif
