// Includes
#include "Function\RankBasedRandomFunction.hpp"
// Library includes
#include <random>
#include <exception>

double RankBasedRandomFunction::execute(int elementCount)
{
	double probabilitySum = 0;
	for (int i = 1; i <= elementCount; i++)
	{
		probabilitySum += 1 + (8 - 1) * exp(-1.0 * (8 - 1) * i / elementCount);
	}

	double randomLine = rand() / RAND_MAX * probabilitySum;
	double partialSum = 0;
	for (int i = 1; i <= elementCount; i++)
	{
		partialSum += 1 + (8 - 1) * exp(-1.0 * (8 - 1) * i / elementCount);
		if (partialSum >= randomLine)
		{
			return i;
		}
	}
	throw std::logic_error("No element has been selected!");
}
