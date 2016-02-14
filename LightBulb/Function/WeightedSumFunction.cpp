// Includes
#include "Function/WeightedSumFunction.hpp"

void WeightedSumFunction::execute(int layerNr, std::vector<Eigen::VectorXd>& activations, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::MatrixXd>& weights)
{
	netInputs[layerNr].noalias() = weights[layerNr - 1] * activations[layerNr - 1];
}

AbstractInputFunction* WeightedSumFunction::getInputFunctionCopy()
{
	return new WeightedSumFunction(*this);
}
