// Includes
#include "Function/ShrinkFunction/ExponentialShrinkFunction.hpp"

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

	AbstractShrinkFunction* ExponentialShrinkFunction::getShrinkFunctionCopy() const
	{
		return new ExponentialShrinkFunction(*this);
	}
}