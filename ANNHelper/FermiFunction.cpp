#include "FermiFunction.hpp"
#include "StandardThreshold.hpp"
#include <math.h>
#include <limits>
#include <stdexcept>

FermiFunction::FermiFunction(float temperatureParameter_)
{
	temperatureParameter = temperatureParameter_;
}

float FermiFunction::execute(float input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold was a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// Consider the threshold
	input -= standardThreshold->getThreshold();
	// Fermi function
	return  1 / (1 + exp(-input / temperatureParameter));
}

float FermiFunction::executeDerivation(float input, AbstractThreshold* threshold)
{
	// Derivation of the Fermi function		
	return execute(input, threshold) * (1 - execute(input, threshold));
}

AbstractActivationFunction* FermiFunction::getActivationFunctionCopy()
{
	return new FermiFunction(*this);
}

float FermiFunction::getMaximum()
{
	return 1;
}

float FermiFunction::getMinimum()
{
	return 0;
}

bool FermiFunction::isLinear()
{
	return false;
}