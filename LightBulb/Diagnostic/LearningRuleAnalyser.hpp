#pragma once

#ifndef _LEARNINGRULEANALYSER_H_
#define _LEARNINGRULEANALYSER_H_

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
	LearningRuleAnalyserOptions()
	{
		learningRule = NULL;
	}
};


class LearningRuleAnalyser
{
private:
	std::unique_ptr<LearningRuleAnalyserOptions> options;

public:
	LearningRuleAnalyser(LearningRuleAnalyserOptions &options_);
	void execute();
	bool switchToNextValueCombination(int startIndex = 0);
	virtual ~LearningRuleAnalyser() {};
};

#endif
