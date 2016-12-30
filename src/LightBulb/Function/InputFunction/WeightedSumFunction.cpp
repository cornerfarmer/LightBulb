// Includes
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

namespace LightBulb
{
	void WeightedSumFunction::execute(int layerNr, const std::vector<Vector> &activations, std::vector<Vector> &netInputs, const std::vector<Matrix> &weights) const
	{
		if (netInputs[layerNr].getCalculatorType() == CT_GPU) 
			netInputs[layerNr].getViennaclValueForEditing() = viennacl::linalg::prod(weights[layerNr - 1].getViennaclValue(), activations[layerNr - 1].getViennaclValue());
		else if(netInputs[layerNr].getCalculatorType() == CT_GPU)
			netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue() * activations[layerNr - 1].getEigenValue();
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction(*this);
	}
}
