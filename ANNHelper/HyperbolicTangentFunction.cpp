#include "HyperbolicTangentFunction.hpp"
#include <limits>
#include <stdexcept>

float HyperbolicTangentFunction::execute(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Return the value of the hyperbolic tangent in this point
	return tanh(input);
}

float HyperbolicTangentFunction::executeDerivation(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Return the value of the derivation of the hyperbolic tangent: 1 / cosh^2
	return 1 / pow(cosh(input), 2);

}

AbstractActivationFunction* HyperbolicTangentFunction::getActivationFunctionCopy()
{
	return new HyperbolicTangentFunction(*this);
}

float HyperbolicTangentFunction::getMaximum()
{
	return 1;
}

float HyperbolicTangentFunction::getMinimum()
{
	return -1;
}

bool HyperbolicTangentFunction::isLinear()
{
	return false;
}