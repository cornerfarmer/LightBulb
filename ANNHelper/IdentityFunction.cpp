#include "IdentityFunction.hpp"
#include <limits>
#include <stdexcept>

float IdentityFunction::execute(float input)
{
	return input;
}

float IdentityFunction::execute(float input, AbstractThreshold* threshold)
{
	return input;
}

float IdentityFunction::executeDerivation(float input, AbstractThreshold* threshold)
{
	return 0;
}

AbstractActivationFunction* IdentityFunction::getActivationFunctionCopy()
{
	return new IdentityFunction(*this);
}

AbstractOutputFunction* IdentityFunction::getOutputFunctionCopy()
{
	return new IdentityFunction(*this);
}

float IdentityFunction::getMaximum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

float IdentityFunction::getMinimum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

bool IdentityFunction::hasAMaxAndMinimum()
{
	return false;
}