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
	template <class Archive>
	friend void serialize(Archive& archive, AbstractReinforcementLearningRule& learningRule);
private:
	protected:
	bool hasLearningSucceeded() override;
	virtual AbstractReinforcementLearningRuleOptions* getOptions();
	void randomGeneretorHasChanged();
public:
	AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_);
	AbstractReinforcementLearningRule() = default;
	std::vector<std::string> getDataSetLabels() override;
};

#include "IO/AbstractReinforcementLearningRuleIO.hpp"

#endif
