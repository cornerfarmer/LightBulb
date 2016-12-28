// Includes
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

namespace LightBulb
{
	void WeightedSumFunction::execute(int layerNr, const std::vector<Vector> &activations, std::vector<Vector> &netInputs, const std::vector<Matrix> &weights) const
	{
		netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue() * activations[layerNr - 1].getEigenValue();
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction(*this);
	}
}
