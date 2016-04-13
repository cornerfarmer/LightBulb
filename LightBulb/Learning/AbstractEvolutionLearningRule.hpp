#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULE_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULE_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations

struct AbstractEvolutionLearningRuleOptions : public AbstractLearningRuleOptions
{
};

// A LearningRule is used to improve a AbstractNeuralNetwork
class AbstractEvolutionLearningRule : public AbstractLearningRule
{
private:
protected:
public:
	AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_);
	AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_);
	static std::vector<std::string> getDataSetLabels();
};

USE_PARENT_SERIALIZATION(AbstractEvolutionLearningRule, AbstractLearningRule);

#endif


