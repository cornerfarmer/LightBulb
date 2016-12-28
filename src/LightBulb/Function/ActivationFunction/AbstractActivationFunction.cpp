// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

namespace LightBulb
{
	void AbstractActivationFunction::execute(int layerNr, std::vector<Vector>& activations, const std::vector<Vector>& netInputs) const
	{
		for (auto i = 0; i < netInputs[layerNr].getEigenValue().rows(); i++)
		{
			(activations[layerNr]).getEigenValueForEditing()(i) = execute(netInputs[layerNr].getEigenValue()(i));
		}
	}

	Vector AbstractActivationFunction::executeDerivation(const Vector& input) const
	{
		Vector output(input.getEigenValue().rows());
		for (auto i = 0; i < input.getEigenValue().rows(); i++)
		{
			output.getEigenValueForEditing()(i) = executeDerivation(input.getEigenValue()(i));
		}
		return output;
	}
}
