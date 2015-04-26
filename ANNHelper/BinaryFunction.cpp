#include "BinaryFunction.hpp"

float BinaryFunction::execute(float input, float threshold)
{
	// If the input is greater than the threshold return 1 else 0
	if (input > threshold)
		return 1;
	else
		return 0;
}

float BinaryFunction::executeDerivation(float input, float threshold)
{
	// TODO: Throw error;
	return 0;
}

AbstractActivationFunction* BinaryFunction::getActivationFunctionCopy()
{
	return new BinaryFunction(*this);
}

float BinaryFunction::getMaximum()
{
	return 1;
}

float BinaryFunction::getMinimum()
{
	return 0;
}

bool BinaryFunction::isLinear()
{
	return false;
}