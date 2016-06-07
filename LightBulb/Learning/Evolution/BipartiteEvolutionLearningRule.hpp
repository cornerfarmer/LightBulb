#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULE_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/AbstractEvolutionLearningRule.hpp"

// Library Includes

// Forward declarations


struct BipartiteEvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
{
	AbstractEvolutionLearningRule* learningRule1;
	AbstractEvolutionLearningRule* learningRule2;

	BipartiteEvolutionLearningRuleOptions()
	{
		learningRule1 = NULL;
		learningRule2 = NULL;
	}
};

class BipartiteEvolutionLearningRule : public AbstractEvolutionLearningRule
{
	template <class Archive>
	friend void serialize(Archive& archive, BipartiteEvolutionLearningRule& learningRule);
	friend struct cereal::LoadAndConstruct<BipartiteEvolutionLearningRule>;
protected:
	BipartiteEvolutionLearningRuleOptions* getOptions();
	bool doIteration();
	void initializeTry();
	bool hasLearningSucceeded();
	void initialize();
	bool exitConditionReached;
	AbstractLearningResult* getLearningResult();
public:
	BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions& options_);
	BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions* options_);
	static std::string getName();
	std::vector<std::string> getDataSetLabels();
	AbstractEvolutionLearningRule* getFirstLearningRule();
	AbstractEvolutionLearningRule* getSecondLearningRule();

};

#include "IO/BipartiteEvolutionLearningRuleIO.hpp"

#endif
