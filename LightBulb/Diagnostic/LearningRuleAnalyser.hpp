#pragma once

#ifndef _LEARNINGRULEANALYSER_H_
#define _LEARNINGRULEANALYSER_H_

// Include
#include "Learning/LearningState.hpp"

// Library includes
#include <memory>
#include <vector>

// Forward declarations
class AbstractChangeableParameter;
class EvolutionLearningRule;
class EvolutionLearningRuleOptions;

struct LearningRuleAnalyserOptions
{
	// A list of parameters whose change effects should be analyzed
	std::vector<AbstractChangeableParameter*> changableParameters;
	// The learning rule which should be analyzed
	EvolutionLearningRule* learningRule;
	// The amount of calculations per parameter combination (the more calculations, the more accurate is the average result, but also the slower is the analyze process!)
	int calculationsPerParameterCombination;

	bool useQualityInsteadOfSuccessful;
	LearningRuleAnalyserOptions()
	{
		learningRule = NULL;
		calculationsPerParameterCombination = 30;
		useQualityInsteadOfSuccessful = false;
	}
};

// This class can be used to analyze the result of a learning rule when changing different parameters
class LearningRuleAnalyser
{
private:
	std::unique_ptr<LearningRuleAnalyserOptions> options;
	// This will switch the parameters to the next combination
	bool switchToNextValueCombination(int startIndex = 0);
public:
	virtual ~LearningRuleAnalyser() {};
	LearningRuleAnalyser(LearningRuleAnalyserOptions &options_);
	// A function for sorting the learning results by their score
	static bool pairCompareBySuccessful(const std::pair<LearningState, std::string>& firstElem, const std::pair<LearningState, std::string>& secondElem);
	static bool pairCompareByQuality(const std::pair<LearningState, std::string>& firstElem, const std::pair<LearningState, std::string>& secondElem);
	// Execute the analyzer: This will execute the learingRule under every possible parameter combination
	void execute();
};

#endif
