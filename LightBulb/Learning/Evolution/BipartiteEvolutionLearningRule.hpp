#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULE_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"

// Library Includes

// Forward declarations


struct BipartiteEvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
{
	EvolutionLearningRule* learningRule1;
	EvolutionLearningRule* learningRule2;

	BipartiteEvolutionLearningRuleOptions()
	{
		learningRule1 = NULL;
		learningRule2 = NULL;
	}
};

class BipartiteEvolutionLearningRule : public AbstractEvolutionLearningRule
{
protected:
	BipartiteEvolutionLearningRuleOptions* getOptions();
	bool doIteration();
	void initializeTry();
	bool hasLearningSucceeded();
	void initialize();
public:
	BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions& options_);
	BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions* options_);
	static std::string getName();
	static std::vector<std::string> getDataSetLabels();
};

#endif
