#include "GaussianRBFFunction.hpp"
#include "RBFThreshold.hpp"
#include <limits>
#include <stdexcept>

float GaussianRBFFunction::execute(float input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold was a StandardThreshold
	if (!rbfThreshold)
		throw std::invalid_argument("The given threshold has to be a RBFThreshold");

	// Return the value of the gaussian rbf: e^(-input^2/(2*width)^2)
	return exp(-pow(input, 2) / (2 * pow(rbfThreshold->getWidth(), 2)));
}

float GaussianRBFFunction::executeDerivation(float input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold was a StandardThreshold
	if (!rbfThreshold)
		throw std::invalid_argument("The given threshold has to be a RBFThreshold");

	// TODO: Implement the derivation even if it is not used
	return 0;

}

AbstractActivationFunction* GaussianRBFFunction::getActivationFunctionCopy()
{
	return new GaussianRBFFunction(*this);
}

float GaussianRBFFunction::getMaximum()
{
	return exp(0.0);
}

float GaussianRBFFunction::getMinimum()
{
	return 0;
}

bool GaussianRBFFunction::isLinear()
{
	return false;
}