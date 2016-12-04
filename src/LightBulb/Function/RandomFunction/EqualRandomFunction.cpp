// Includes
#include "LightBulb/Function/RandomFunction/EqualRandomFunction.hpp"
// Library includes
#include <random>
#include <algorithm>

namespace LightBulb
{
	int EqualRandomFunction::execute(int elementCount) const
	{
		return randomGenerator->randInt(0, elementCount - 1);
	}

	AbstractCloneable* EqualRandomFunction::clone() const
	{
		return new EqualRandomFunction(*this);
	}
}
