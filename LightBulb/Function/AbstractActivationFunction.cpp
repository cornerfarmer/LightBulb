// Includes
#include "Function/AbstractActivationFunction.hpp"

void AbstractActivationFunction::execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs)
{
	for (auto i = 0; i < netInputs[layerNr].rows(); i++)
	{
		(*activations[layerNr])(i) = execute(netInputs[layerNr](i));
	}
}

Eigen::VectorXd AbstractActivationFunction::executeDerivation(Eigen::VectorXd input)
{
	Eigen::VectorXd output(input.rows());
	for (auto i = 0; i < input.rows(); i++)
	{
		output(i) = executeDerivation(input(i));
	}
	return output;
}
