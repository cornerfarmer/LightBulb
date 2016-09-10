// Includes
#include "Function/ActivationFunction/HyperbolicTangentFunction.hpp"
// Library includes
#include <limits>
#include <stdexcept>

namespace LightBulb
{
	double HyperbolicTangentFunction::execute(double input)
	{
		// Return the value of the hyperbolic tangent in this point
		return tanh(input);
	}

	double HyperbolicTangentFunction::executeDerivation(double input)
	{
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
}