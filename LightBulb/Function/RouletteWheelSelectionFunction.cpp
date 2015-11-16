// Includes
#include "Function/RouletteWheelSelectionFunction.hpp"
// Library includes
#include <random>
#include <stdexcept>

int RouletteWheelSelectionFunction::execute(const std::vector<double> &probabilities)
{
	double probabilitySum = 0;
	for (auto probability = probabilities.begin(); probability != probabilities.end(); probability++)
	{
		probabilitySum += *probability;
	}

	double randomLine = (float)rand() / RAND_MAX * probabilitySum;
	double partialSum = 0;
	int index = 0;
	for (auto probability = probabilities.begin(); probability != probabilities.end(); probability++, index++)
	{
		partialSum += *probability;
		if (partialSum >= randomLine)
		{
			return index;
		}
	}
	throw std::logic_error("No element has been selected!");
}

std::vector<int> RouletteWheelSelectionFunction::execute(const std::vector<double> &probabilities, int selectionCount)
{
	if (selectionCount <= 0)
		throw std::invalid_argument("The selectionCount has to be greater than 0!");

	double probabilitySum = 0;
	for (auto probability = probabilities.begin(); probability != probabilities.end(); probability++)
	{
		probabilitySum += *probability;
	}

	double stepSize = probabilitySum / selectionCount;
	int currentStep = 0;
	double partialSum = 0;
	std::vector<int> selection;
	selection.reserve(selectionCount);
	int index = 0;
	for (auto probability = probabilities.begin(); probability != probabilities.end(); probability++, index++)
	{
		partialSum += *probability;
		while (currentStep < selectionCount && partialSum >= currentStep * stepSize)
		{
			selection.push_back(index);
			currentStep++;
		}
	}

	if (currentStep != selectionCount)
		throw std::logic_error("Not the right amount of elements has been selected!");

	return selection;
}