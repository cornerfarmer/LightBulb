// Includes
#include "Function\FermiFunction.hpp"
#include "Neuron\StandardThreshold.hpp"
// Library includes
#include <math.h>
#include <limits>
#include <stdexcept>

FermiFunction::FermiFunction(double temperatureParameter_)
{
	temperatureParameter = temperatureParameter_;
}

double FermiFunction::execute(double input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold is a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// Consider the threshold
	input -= standardThreshold->getThreshold();
	// Execture the fermi function
	return  1 / (1 + exp(-input / temperatureParameter));
}

double FermiFunction::executeDerivation(double input, AbstractThreshold* threshold)
{
	// Execute the derivation of the Fermi function		
	return execute(input, threshold) * (1 - execute(input, threshold));
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