// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Function/ActivationFunction/HyperbolicTangentFunction.hpp"
// Library includes

namespace LightBulb
{
	double HyperbolicTangentFunction::execute(double input) const
	{
		// Return the value of the hyperbolic tangent in this point
		return tanh(input);
	}

	double HyperbolicTangentFunction::executeDerivation(double input) const
	{
		// Return the value of the derivation of the hyperbolic tangent: 1 / cosh^2
		return 1 / pow(cosh(input), 2);

	}

	AbstractCloneable* HyperbolicTangentFunction::clone() const
	{
		return new HyperbolicTangentFunction(*this);
	}

	double HyperbolicTangentFunction::getMaximum() const
	{
		return 1;
	}

	double HyperbolicTangentFunction::getMinimum() const
	{
		return -1;
	}

	bool HyperbolicTangentFunction::hasAMaxAndMinimum() const
	{
		return true;
	}
}