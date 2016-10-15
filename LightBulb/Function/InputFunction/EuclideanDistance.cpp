// Includes
#include "Function/InputFunction/EuclideanDistance.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

namespace LightBulb
{
	void EuclideanDistance::execute(int layerNr, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, std::vector<Eigen::VectorXd>& netInputs, const std::vector<Eigen::MatrixXd>& weights) const
	{
		netInputs[layerNr].noalias() = (weights[layerNr - 1].rowwise() - activations[layerNr - 1].transpose()).rowwise().squaredNorm().cwiseSqrt().transpose();
	}

	AbstractInputFunction* EuclideanDistance::getInputFunctionCopy() const
	{
		return new EuclideanDistance(*this);
	}
}