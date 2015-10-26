#include "Diagnostic/LearningRuleAnalyser.hpp"
#include "Diagnostic/AbstractChangeableParameter.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
// Library include
#include <iostream>
#include <algorithm>
#include <vector>

LearningRuleAnalyser::LearningRuleAnalyser(LearningRuleAnalyserOptions &options_)
{
	options.reset(new LearningRuleAnalyserOptions(options_));
}


bool LearningRuleAnalyser::pairCompare(const std::pair<LearningResult, std::string>& firstElem, const std::pair<LearningResult, std::string>& secondElem)
{
	// Prefer learingResults which were more successful and only consider speed if the successful values are equal
	return firstElem.first.successful > secondElem.first.successful || (firstElem.first.successful == secondElem.first.successful && firstElem.first.iterationsNeeded < secondElem.first.iterationsNeeded);
}

void LearningRuleAnalyser::execute()
{
	// Reset all parameters
	for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
	{
		(*changableParameter)->resetToStart();
	}

	// A vector which holds the learning result of every parameter combination
	std::vector<std::pair<LearningResult, std::string>> combinations;
	do
	{
		// Go through all parameters and print them
		std::string parameterCombination = "|";
		for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
		{
			parameterCombination += (*changableParameter)->printCurrentValue();
			parameterCombination += "|";
		}
		std::cout << parameterCombination;

		// Execute the learning rule multiple times with the current parameter combination so we get stable average values
		LearningResult summaryResult;
		for (int i = 0; i < options->calculationsPerParameterCombination; i++)
		{
			LearningResult currentResult = options->learningRule->doLearning();
			summaryResult.successful += currentResult.successful;
			summaryResult.iterationsNeeded += currentResult.iterationsNeeded;
		}

		// Add the result to the vector
		combinations.push_back(make_pair(summaryResult ,parameterCombination));

		// Print the result
		std::cout << ": " << summaryResult.successful << "/" << options->calculationsPerParameterCombination << " successful after " << summaryResult.iterationsNeeded / options->calculationsPerParameterCombination << " iterations";
		std::cout << std::endl;
		// Switch to the next parameter combination as long as we have not tested all yet
	} while (!switchToNextValueCombination());

	// Sort the all tested combinations
	std::sort(combinations.begin(), combinations.end(), LearningRuleAnalyser::pairCompare);

	// Print the best combinations
	int place = 1;
	for (auto combination = combinations.begin(); combination != combinations.end() && place <= 3; combination++, place++)
	{
		std::cout << place << ". " << combination->second << ": " << combination->first.successful << "/" << options->calculationsPerParameterCombination << " successful after " << combination->first.iterationsNeeded / options->calculationsPerParameterCombination << " iterations" << std::endl;
	}

}

bool LearningRuleAnalyser::switchToNextValueCombination(int startIndex)
{
	bool switchThisValue = true;
	// If this is not the last parameter
	if (startIndex < options->changableParameters.size() - 1)
	{
		// First switch the next parameter
		switchThisValue = switchToNextValueCombination(startIndex + 1);
	}

	// Only change this parameter if its the last one or if the next parameter already reached the end of its test interval
	if (switchThisValue)
		return options->changableParameters[startIndex]->switchToNextValue();
	else
		return false;
}
