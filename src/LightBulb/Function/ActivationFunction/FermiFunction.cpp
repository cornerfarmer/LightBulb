// Includes
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
// Library includes
#include <math.h>
#include <limits>
#include <stdexcept>

namespace LightBulb
{
	FermiFunction::FermiFunction(double temperatureParameter_)
	{
		temperatureParameter = temperatureParameter_;
	}

	double FermiFunction::execute(double input) const
	{
		// Execture the fermi function
		return  1 / (1 + exp(-input / temperatureParameter));
	}

	double FermiFunction::executeDerivation(double input) const
	{
		// Execute the derivation of the Fermi function		
		return execute(input) * (1 - execute(input));
	}

	AbstractCloneable* FermiFunction::clone() const
	{
		return new FermiFunction(*this);
	}

	double FermiFunction::getMaximum() const
	{
		return 1;
	}

	double FermiFunction::getMinimum() const
	{
		return 0;
	}

	bool FermiFunction::hasAMaxAndMinimum() const
	{
		return true;
	}
}