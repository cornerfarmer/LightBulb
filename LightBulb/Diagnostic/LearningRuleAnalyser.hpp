#pragma once

#ifndef _LEARNINGRULEANALYSER_H_
#define _LEARNINGRULEANALYSER_H_

// Include
#include "Learning/LearningResult.hpp"

// Library includes
#include <memory>
#include <vector>

// Forward declarations
class AbstractChangeableParameter;
class EvolutionLearningRule;
class EvolutionLearningRuleOptions;

struct LearningRuleAnalyserOptions
{
	std::vector<AbstractChangeableParameter*> changableParameters;
	EvolutionLearningRule* learningRule;
	int calculationsPerParameterCombination;
	LearningRuleAnalyserOptions()
	{
		learningRule = NULL;
		calculationsPerParameterCombination = 30;
	}
};


class LearningRuleAnalyser
{
private:
	std::unique_ptr<LearningRuleAnalyserOptions> options;

public:
	LearningRuleAnalyser(LearningRuleAnalyserOptions &options_);
	static bool pairCompare(const std::pair<LearningResult, std::string>& firstElem, const std::pair<LearningResult, std::string>& secondElem);
	void execute();
	bool switchToNextValueCombination(int startIndex = 0);
	virtual ~LearningRuleAnalyser() {};
};

#endif
