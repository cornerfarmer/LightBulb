// Includes
#include "LightBulb/Function/SelectionFunction/RouletteWheelSelectionFunction.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
// Library includes
#include <stdexcept>

namespace LightBulb
{
	int RouletteWheelSelectionFunction::execute(const std::vector<double> &probabilities) const
	{
		double probabilitySum = 0;
		for (auto probability = probabilities.begin(); probability != probabilities.end(); probability++)
		{
			probabilitySum += *probability;
		}

		double randomLine = randomGenerator->randFloat() * probabilitySum;
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

	std::vector<int> RouletteWheelSelectionFunction::execute(const std::vector<double> &probabilities, int selectionCount) const
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

	AbstractCloneable* RouletteWheelSelectionFunction::clone() const
	{
		return new RouletteWheelSelectionFunction(*this);
	}
}
