// Includes
#include "Function/ExponentialShrinkFunction.hpp"


ExponentialShrinkFunction::ExponentialShrinkFunction(double startValue_, double minValue_, double speedFactor_)
	: AbstractShrinkFunction(startValue_, minValue_)
{
	speedFactor = speedFactor_;
}

double ExponentialShrinkFunction::execute(double time)
{
	return startValue * exp(-1 * time / speedFactor) + minValue;
}

AbstractShrinkFunction* ExponentialShrinkFunction::getShrinkFunctionCopy()
{
	return new ExponentialShrinkFunction(*this);
}