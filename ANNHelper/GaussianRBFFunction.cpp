#include "GaussianRBFFunction.hpp"
#include "RBFThreshold.hpp"
#include <limits>
#include <stdexcept>

float GaussianRBFFunction::execute(float input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold is a RBFThreshold
	if (!rbfThreshold)
		throw std::invalid_argument("The given threshold has to be a RBFThreshold");

	// Return the value of the gaussian rbf: e^(-input^2/(2*width^2)
	return exp(-pow(input, 2) / (2 * pow(rbfThreshold->getWidth(), 2)));
}

float GaussianRBFFunction::executeDerivation(float input, AbstractThreshold* threshold)
{
	RBFThreshold* rbfThreshold = dynamic_cast<RBFThreshold*>(threshold);
	// Check if the given threshold was a RBFThreshold
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
	throw std::logic_error("A GaussianRBFFunction does not have a maximum");
}

float GaussianRBFFunction::getMinimum()
{
	throw std::logic_error("A GaussianRBFFunction does not have a minimum");
}

bool GaussianRBFFunction::hasAMaxAndMinimum()
{
	return true;
}