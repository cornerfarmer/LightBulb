#pragma once

#ifndef _MONTECARLOLEARNINGRULE_H_
#define _MONTECARLOLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include <Teaching/Teacher.hpp>
#include <Learning/ResilientLearningRateHelper.hpp>
#include <Learning/BackpropagationLearningRule.hpp>

// Library Includes
#include <vector>

// Forward declarations
class AbstractNetworkTopology;

struct MonteCarloLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
{
	double discountingFactor;
	MonteCarloLearningRuleOptions()
	{
		discountingFactor = 0.99;
	}
};


class MonteCarloLearningRule : public AbstractReinforcementLearningRule
{
private:
	Teacher teacher;
	std::unique_ptr<BackpropagationLearningRule> backpropagationLearningRule;
	std::vector<std::vector<double>> teachingPatterns;
	std::vector<std::vector<double>> teachingInputs;
	std::vector<int> chosenActions;
	void initialize();
	void addTrainingPattern(AbstractNetworkTopology* networkTopology, double reward);
	void doSupervisedLearning();
protected:
	bool doIteration();
	MonteCarloLearningRuleOptions* getOptions();
	AbstractLearningResult* getLearningResult();
public:
	MonteCarloLearningRule(MonteCarloLearningRuleOptions& options_);
	MonteCarloLearningRule(MonteCarloLearningRuleOptions* options_);
	MonteCarloLearningRule();
	// Executes the learning process
	void initializeTry();
	static std::string getName();
	std::vector<std::string> getDataSetLabels();
};


#endif
