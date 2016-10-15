// Includes
#include "Function/ActivationFunction/IdentityFunction.hpp"
// Library includes
#include <limits>
#include <stdexcept>

namespace LightBulb
{
	double IdentityFunction::execute(double input) const
	{
		return input;
	}

	void IdentityFunction::execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const std::vector<Eigen::VectorXd>& netInputs) const
	{
		activations[layerNr] = netInputs[layerNr];
	}

	double IdentityFunction::executeDerivation(double input) const
	{
		return 1;
	}

	AbstractActivationFunction* IdentityFunction::getActivationFunctionCopy() const
	{
		return new IdentityFunction(*this);
	}


	double IdentityFunction::getMaximum() const
	{
		throw std::logic_error("A IdentityFunction does not have a maximum");
	}

	double IdentityFunction::getMinimum() const
	{
		throw std::logic_error("A IdentityFunction does not have a maximum");
	}

	bool IdentityFunction::hasAMaxAndMinimum() const
	{
		return false;
	}
}