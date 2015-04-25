#include "HyperbolicTangentFunction.hpp"
#include <limits>
#include <exception>

float HyperbolicTangentFunction::execute(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Return the value of the hyperbolic tangent in this point
	float output = tanh(input);
	
	// Check the calculated value is valid
	if (output == std::numeric_limits<float>::infinity())
		throw std::exception();

	return output;
}

float HyperbolicTangentFunction::executeDerivation(float input, float threshold)
{
	// Consider the threshold
	input -= threshold;
	// Return the value of the derivation of the hyperbolic tangent: 1 / cosh^2
	float output = 1 / pow(cosh(input), 2);

	// Check the calculated value is valid
	if (output == std::numeric_limits<float>::infinity())
		throw std::exception();

	return output;
}

ActivationFunction* HyperbolicTangentFunction::getActivationFunctionCopy()
{
	return new HyperbolicTangentFunction(*this);
}