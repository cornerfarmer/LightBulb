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
