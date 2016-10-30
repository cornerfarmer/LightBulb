// Includes
#include "Function/RandomFunction/EqualRandomFunction.hpp"
// Library includes
#include <random>
#include <algorithm>

namespace LightBulb
{
	int EqualRandomFunction::execute(int elementCount) const
	{
		return randomGenerator->randInt(0, elementCount - 1);
	}

	AbstractRandomFunction* EqualRandomFunction::clone()
	{
		return new EqualRandomFunction(*this);
	}
}
