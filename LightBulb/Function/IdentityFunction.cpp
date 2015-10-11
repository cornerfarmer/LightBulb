// Includes
#include "Function/IdentityFunction.hpp"
// Library includes
#include <limits>
#include <stdexcept>

double IdentityFunction::execute(double input)
{
	return input;
}

double IdentityFunction::execute(double input, AbstractThreshold* threshold)
{
	return input;
}

double IdentityFunction::executeDerivation(double input, AbstractThreshold* threshold)
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

double IdentityFunction::getMaximum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

double IdentityFunction::getMinimum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

bool IdentityFunction::hasAMaxAndMinimum()
{
	return false;
}