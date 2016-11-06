// Includes
#include "Function/InputFunction/WeightedSumFunction.hpp"

namespace LightBulb
{
	void WeightedSumFunction::execute(int layerNr, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, std::vector<Eigen::VectorXd>& netInputs, const std::vector<Eigen::MatrixXd>& weights) const
	{
		netInputs[layerNr].noalias() = weights[layerNr - 1] * activations[layerNr - 1];
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction(*this);
	}
}