// Includes
#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
// Library includes
#include <stdexcept>
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	BinaryFunction::BinaryFunction(double minValue_, double maxValue_)
	{
		minValue = minValue_;
		maxValue = maxValue_;
	}

	double BinaryFunction::execute(double input) const
	{
		// If the input is greater than the threshold return 1 else 0
		if (input > 0)
			return maxValue;
		else
			return minValue;
	}

	double BinaryFunction::executeDerivation(double input) const
	{
		// A binary function does not have a derivation => throw a exception
		throw std::logic_error("There is no derivation of the binary function");
	}

	AbstractCloneable* BinaryFunction::clone() const
	{
		return new BinaryFunction(*this);
	}

	double BinaryFunction::getMaximum() const
	{
		return maxValue;
	}

	double BinaryFunction::getMinimum() const
	{
		return minValue;
	}

	bool BinaryFunction::hasAMaxAndMinimum() const
	{
		return true;
	}


	void BinaryFunction::execute(int layerNr, std::vector<Vector<>>& activations, const std::vector<Vector<>>& netInputs) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("binary_function", "binary_assign", "binary_function.cl");
			executeVectorAssignKernel(kernel, netInputs[layerNr].getViennaclValue(), activations[layerNr].getViennaclValueForEditing());
		}
		else
		{
			AbstractActivationFunction::execute(layerNr, activations, netInputs);
		}
	}

}
