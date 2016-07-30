#pragma once

#ifndef _ABSTRACTREINFORCEMENTLEARNINGRULEINGRULE_H_
#define _ABSTRACTREINFORCEMENTLEARNINGRULEINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"

// Library Includes

// Forward declarations
class AbstractReinforcementWorld;

struct AbstractReinforcementLearningRuleOptions : public AbstractLearningRuleOptions
{
	AbstractReinforcementWorld* world;
	AbstractReinforcementLearningRuleOptions()
	{
		world = NULL;
		maxIterationsPerTry = 10000000000;
	}
};

#define DATA_SET_REWARD "Reward"

class AbstractReinforcementLearningRule : public AbstractLearningRule
{
private:
	protected:
	bool hasLearningSucceeded();
	virtual AbstractReinforcementLearningRuleOptions* getOptions();
public:
	AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_);
	AbstractReinforcementLearningRule() = default;
	std::vector<std::string> getDataSetLabels();
};


#endif
