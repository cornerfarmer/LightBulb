// Includes
#include "Function/BinaryFunction.hpp"
#include "Neuron/StandardThreshold.hpp"
// Library includes
#include <stdexcept>

BinaryFunction::BinaryFunction(double minValue_, double maxValue_)
{
	minValue = minValue_;
	maxValue = maxValue_;
}

double BinaryFunction::execute(double input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold is a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// If the input is greater than the threshold return 1 else 0
	if (input > standardThreshold->getThreshold())
		return maxValue;
	else
		return minValue;
}

double BinaryFunction::executeDerivation(double input, AbstractThreshold* threshold)
{
	// A binary function does not have a derivation => throw a exception
	throw std::logic_error("There is no derivation of the binary function");
}

AbstractActivationFunction* BinaryFunction::getActivationFunctionCopy()
{
	return new BinaryFunction(*this);
}

double BinaryFunction::getMaximum()
{
	return maxValue;
}

double BinaryFunction::getMinimum()
{
	return minValue;
}

bool BinaryFunction::hasAMaxAndMinimum()
{
	return true;
}