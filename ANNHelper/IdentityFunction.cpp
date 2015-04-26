#include "IdentityFunction.hpp"
#include <limits>

float IdentityFunction::execute(float input)
{
	return input;
}

float IdentityFunction::execute(float input, float threshold)
{
	return input;
}

float IdentityFunction::executeDerivation(float input, float threshold)
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
	return std::numeric_limits<float>::infinity();
}

float IdentityFunction::getMinimum()
{
	return -std::numeric_limits<float>::infinity();
}

bool IdentityFunction::isLinear()
{
	return true;
}