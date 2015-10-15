#include "Diagnostic/LearningRuleAnalyser.hpp"
#include "Diagnostic/AbstractChangeableParameter.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
// Library include
#include <iostream>
LearningRuleAnalyser::LearningRuleAnalyser(LearningRuleAnalyserOptions &options_)
{
	options.reset(new LearningRuleAnalyserOptions(options_));
}

void LearningRuleAnalyser::execute()
{
	for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
	{
		(*changableParameter)->resetToStart();
	}

	do
	{
		std::cout << "|";
		for (auto changableParameter = options->changableParameters.begin(); changableParameter != options->changableParameters.end(); changableParameter++)
		{
			(*changableParameter)->printCurrentValue();
			std::cout << "|";
		}
		std::cout << std::endl;
		options->learningRule->doLearning();
	} while (!switchToNextValueCombination());
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
