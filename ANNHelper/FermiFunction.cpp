#include "FermiFunction.hpp"
#include <math.h>
#include <limits>
#include <exception>

FermiFunction::FermiFunction(float temperatureParameter_)
{
	temperatureParameter = temperatureParameter_;
}

float FermiFunction::execute(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Fermi function
	float output = 1 / (1 + exp(-input / temperatureParameter));

	// Check the calculated value is valid
	if (output == std::numeric_limits<float>::infinity())
		throw std::exception();

	return output;
}

float FermiFunction::executeDerivation(float input, float threshold)
{
	// Derivation of the Fermi function
	float output = execute(input, threshold) * (1 - execute(input, threshold));

	// Check the calculated value is valid
	if (output == std::numeric_limits<float>::infinity())
		throw std::exception();
			
	return output;
}

ActivationFunction* FermiFunction::getActivationFunctionCopy()
{
	return new FermiFunction(*this);
}