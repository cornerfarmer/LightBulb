#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULE_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULE_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class AbstractEvolutionWorld;

struct AbstractEvolutionLearningRuleOptions : public AbstractLearningRuleOptions
{
	AbstractEvolutionWorld* world;
	AbstractEvolutionLearningRuleOptions()
	{
		world = NULL;
	}
};

// A LearningRule is used to improve a AbstractNeuralNetwork
class AbstractEvolutionLearningRule : public AbstractLearningRule
{
	friend class BipartiteEvolutionLearningRule;
private:
protected:
	AbstractEvolutionLearningRuleOptions* getOptions();
public:
	AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_);
	AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_);
	std::vector<std::string> getDataSetLabels();
	virtual AbstractEvolutionWorld* getWorld();
};

USE_PARENT_SINGLE_SERIALIZATION(AbstractEvolutionLearningRule, AbstractLearningRule);

#endif


