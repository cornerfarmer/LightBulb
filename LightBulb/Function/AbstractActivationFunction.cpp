// Includes
#include "Function/AbstractActivationFunction.hpp"

void AbstractActivationFunction::execute(int layerNr, std::vector<Eigen::VectorXd>& activations, std::vector<Eigen::VectorXd>& netInputs)
{
	for (auto i = 0; i < netInputs[layerNr].cols(); i++)
	{
		activations[layerNr](i) = execute(netInputs[layerNr](i));
	}
}
