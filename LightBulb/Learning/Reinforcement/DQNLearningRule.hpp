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
	double discountingFactor;
	DQNLearningRuleOptions()
	{
		discountingFactor = 0.99;
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
	Teacher teacher;
	std::vector<Transition> transitions;
	std::unique_ptr<BackpropagationLearningRule> backpropagationLearningRule;
	std::unique_ptr<AbstractNeuralNetwork> steadyNetwork;
	void initialize();
	void storeTransition(AbstractNetworkTopology* networkTopology, double reward);
	void doSupervisedLearning();
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
