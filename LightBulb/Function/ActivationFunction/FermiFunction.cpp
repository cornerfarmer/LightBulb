// Includes
#include "Function/ActivationFunction/FermiFunction.hpp"
// Library includes
#include <math.h>
#include <limits>
#include <stdexcept>

FermiFunction::FermiFunction(double temperatureParameter_)
{
	temperatureParameter = temperatureParameter_;
}

double FermiFunction::execute(double input)
{
	// Execture the fermi function
	return  1 / (1 + exp(-input / temperatureParameter));
}

double FermiFunction::executeDerivation(double input)
{
	// Execute the derivation of the Fermi function		
	return execute(input) * (1 - execute(input));
}

AbstractActivationFunction* FermiFunction::getActivationFunctionCopy()
{
	return new FermiFunction(*this);
}

double FermiFunction::getMaximum()
{
	return 1;
}

double FermiFunction::getMinimum()
{
	return 0;
}

bool FermiFunction::hasAMaxAndMinimum()
{
	return true;
}