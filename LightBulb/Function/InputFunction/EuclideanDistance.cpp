// Includes
#include "Function/InputFunction/EuclideanDistance.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

void EuclideanDistance::execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>& activations, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::MatrixXd>& weights)
{
	Eigen::MatrixXd sub = (weights[layerNr - 1].rowwise() - activations[layerNr - 1]->transpose());
	netInputs[layerNr].noalias() = (weights[layerNr - 1].rowwise() - activations[layerNr - 1]->transpose()).rowwise().squaredNorm().cwiseSqrt().transpose();
}

AbstractInputFunction* EuclideanDistance::getInputFunctionCopy()
{
	return new EuclideanDistance(*this);
}
