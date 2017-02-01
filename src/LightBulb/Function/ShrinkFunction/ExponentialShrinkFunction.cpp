// Includes
#include "LightBulb/Function/ShrinkFunction/ExponentialShrinkFunction.hpp"
#include <cmath>

namespace LightBulb
{
	ExponentialShrinkFunction::ExponentialShrinkFunction(double startValue_, double minValue_, double speedFactor_)
		: AbstractShrinkFunction(startValue_, minValue_)
	{
		speedFactor = speedFactor_;
	}

	double ExponentialShrinkFunction::execute(double time) const
	{
		return startValue * exp(-1 * time / speedFactor) + minValue;
	}

	AbstractCloneable* ExponentialShrinkFunction::clone() const
	{
		return new ExponentialShrinkFunction(*this);
	}
}