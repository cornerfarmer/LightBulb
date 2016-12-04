// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"

namespace LightBulb
{
	void AbstractActivationFunction::execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const std::vector<Eigen::VectorXd>& netInputs) const
	{
		for (auto i = 0; i < netInputs[layerNr].rows(); i++)
		{
			(activations[layerNr])(i) = execute(netInputs[layerNr](i));
		}
	}

	Eigen::VectorXd AbstractActivationFunction::executeDerivation(const Eigen::VectorXd& input) const
	{
		Eigen::VectorXd output(input.rows());
		for (auto i = 0; i < input.rows(); i++)
		{
			output(i) = executeDerivation(input(i));
		}
		return output;
	}
}