// Includes
#include "Function/ActivationFunction/IdentityFunction.hpp"
// Library includes
#include <limits>
#include <stdexcept>

double IdentityFunction::execute(double input)
{
	return input;
}

void IdentityFunction::execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs)
{
	*activations[layerNr] = netInputs[layerNr];
}

double IdentityFunction::executeDerivation(double input)
{
	return 1;
}

AbstractActivationFunction* IdentityFunction::getActivationFunctionCopy()
{
	return new IdentityFunction(*this);
}

AbstractOutputFunction* IdentityFunction::getOutputFunctionCopy()
{
	return new IdentityFunction(*this);
}

double IdentityFunction::getMaximum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

double IdentityFunction::getMinimum()
{
	throw std::logic_error("A IdentityFunction does not have a maximum");
}

bool IdentityFunction::hasAMaxAndMinimum()
{
	return false;
}