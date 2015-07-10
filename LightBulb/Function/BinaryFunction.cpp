#include "Function\BinaryFunction.hpp"
#include "Neuron\StandardThreshold.hpp"
#include <stdexcept>

double BinaryFunction::execute(double input, AbstractThreshold* threshold)
{
	StandardThreshold* standardThreshold = dynamic_cast<StandardThreshold*>(threshold);
	// Check if the given threshold is a StandardThreshold
	if (!standardThreshold)
		throw std::invalid_argument("The given threshold has to be a StandardThreshold");

	// If the input is greater than the threshold return 1 else 0
	if (input > standardThreshold->getThreshold())
		return 1;
	else
		return 0;
}

double BinaryFunction::executeDerivation(double input, AbstractThreshold* threshold)
{
	// A binary function does not have a derivation => throw a exception
	throw std::logic_error("There is no derivation of the binary function");
	return 0;
}

AbstractActivationFunction* BinaryFunction::getActivationFunctionCopy()
{
	return new BinaryFunction(*this);
}

double BinaryFunction::getMaximum()
{
	return 1;
}

double BinaryFunction::getMinimum()
{
	return 0;
}

bool BinaryFunction::hasAMaxAndMinimum()
{
	return true;
}