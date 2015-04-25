#include "IdentityFunction.hpp"

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

ActivationFunction* IdentityFunction::getActivationFunctionCopy()
{
	return new IdentityFunction(*this);
}

OutputFunction* IdentityFunction::getOutputFunctionCopy()
{
	return new IdentityFunction(*this);
}