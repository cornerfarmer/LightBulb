// Includes
#include "Function\HyperbolicTangentFunction.hpp"
#include "Neuron\StandardThreshold.hpp"
// Library includes
#include <limits>
#include <stdexcept>

double HyperbolicTangentFunction::execute(double input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold is a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// Consider the threshold
	input -= standardThreshold->getThreshold();
	// Return the value of the hyperbolic tangent in this point
	return tanh(input);
}

double HyperbolicTangentFunction::executeDerivation(double input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold is a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// Consider the threshold
	input -= standardThreshold->getThreshold();
	// Return the value of the derivation of the hyperbolic tangent: 1 / cosh^2
	return 1 / pow(cosh(input), 2);

}

AbstractActivationFunction* HyperbolicTangentFunction::getActivationFunctionCopy()
{
	return new HyperbolicTangentFunction(*this);
}

double HyperbolicTangentFunction::getMaximum()
{
	return 1;
}

double HyperbolicTangentFunction::getMinimum()
{
	return -1;
}

bool HyperbolicTangentFunction::hasAMaxAndMinimum()
{
	return true;
}