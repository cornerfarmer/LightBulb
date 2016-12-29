// Includes
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

namespace LightBulb
{
	void AbstractActivationFunction::execute(int layerNr, std::vector<Vector>& activations, const std::vector<Vector>& netInputs) const
	{
		if (netInputs[layerNr].getCalculatorType() == CT_GPU)
		{
			for (auto i = 0; i < netInputs[layerNr].getViennaclValue().size(); i++)
			{
				(activations[layerNr]).getViennaclValueForEditing()(i) = execute(netInputs[layerNr].getViennaclValue()(i));
			}
		}
		else
		{
			for (auto i = 0; i < netInputs[layerNr].getEigenValue().rows(); i++)
			{
				(activations[layerNr]).getEigenValueForEditing()(i) = execute(netInputs[layerNr].getEigenValue()(i));
			}
		}
	}

	Vector AbstractActivationFunction::executeDerivation(const Vector& input) const
	{
		Vector output(input.getCalculatorType() == CT_GPU ? input.getViennaclValue().size() : input.getEigenValue().rows());
		if (input.getCalculatorType() == CT_GPU)
		{
			for (auto i = 0; i < input.getViennaclValue().size(); i++)
			{
				output.getViennaclValueForEditing()(i) = executeDerivation(input.getViennaclValue()(i));
			}
		}
		else
		{
			for (auto i = 0; i < input.getEigenValue().rows(); i++)
			{
				output.getEigenValueForEditing()(i) = executeDerivation(input.getEigenValue()(i));
			}
		}
		return output;
	}
}
