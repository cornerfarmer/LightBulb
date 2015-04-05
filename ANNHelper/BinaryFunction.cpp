#include "BinaryFunction.hpp"

float BinaryFunction::execute(float input, float threshold)
{
	// If the input is greater than the threshold return 1 else 0
	if (input > threshold)
		return 1;
	else
		return 0;
}

float BinaryFunctionexecuteDerivation(float input, float threshold)
{
	// TODO: Throw error;
	return 0;
}