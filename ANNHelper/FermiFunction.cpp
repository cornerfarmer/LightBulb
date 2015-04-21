#include "FermiFunction.hpp"
#include <math.h>

FermiFunction::FermiFunction(float temperatureParameter_)
{
	temperatureParameter = temperatureParameter_;
}

float FermiFunction::execute(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Fermi function
	return 1 / (1 + exp(-input / temperatureParameter));
}

float FermiFunction::executeDerivation(float input, float threshold)
{
	// Derivation of the Fermi function
	return execute(input, threshold) * (1 - execute(input, threshold));
}