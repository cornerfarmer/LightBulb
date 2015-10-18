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


bool LearningRuleAnalyser::pairCompare(const std::pair<LearningResult, std::string>& firstElem, const std::pair<LearningResult, std::string>& secondElem) {
	return firstElem.first.successful < secondElem.first.successful || (firstElem.first.successful == secondElem.first.successful && firstElem.first.iterationsNeeded < secondElem.first.iterationsNeeded);
}

void LearningRuleAnalyser::execute()
{
	for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
	{
		(*changableParameter)->resetToStart();
	}

	std::vector<std::pair<LearningResult, std::string>> combinations;

	do
	{
		std::string parameterCombination = "|";
		for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
		{
			parameterCombination += (*changableParameter)->printCurrentValue();
			parameterCombination += "|";
		}
		std::cout << parameterCombination;

		LearningResult summaryResult;
		for (int i = 0; i < options->calculationsPerParameterCombination; i++)
		{
			LearningResult currentResult = options->learningRule->doLearning();
			summaryResult.successful += currentResult.successful;
			summaryResult.iterationsNeeded += currentResult.iterationsNeeded;
		}

		combinations.push_back(make_pair(summaryResult ,parameterCombination));

		std::cout << ": " << summaryResult.successful << "/" << options->calculationsPerParameterCombination << " successful after " << summaryResult.iterationsNeeded / options->calculationsPerParameterCombination << " iterations";
		std::cout << std::endl;
	} while (!switchToNextValueCombination());

	std::sort(combinations.begin(), combinations.end(), LearningRuleAnalyser::pairCompare);

	int place = 1;
	for (auto combination = combinations.begin(); combination != combinations.end() && place <= 3; combination++, place++)
	{
		std::cout << place << ". " << combination->second << ": " << combination->first.successful << "/" << options->calculationsPerParameterCombination << " successful after " << combination->first.iterationsNeeded / options->calculationsPerParameterCombination << " iterations" << std::endl;
	}

}

bool LearningRuleAnalyser::switchToNextValueCombination(int startIndex)
{
	bool switchThisValue = true;
	if (startIndex < options->changableParameters.size() - 1)
	{
		switchThisValue = switchToNextValueCombination(startIndex + 1);
	}

	if (switchThisValue)
		return options->changableParameters[startIndex]->switchToNextValue();
	else
		return false;
}
