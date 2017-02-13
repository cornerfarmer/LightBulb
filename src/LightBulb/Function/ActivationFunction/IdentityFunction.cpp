// Includes
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
// Library includes
#include <stdexcept>
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	double IdentityFunction::execute(double input) const
	{
		return input;
	}

	void IdentityFunction::execute(int layerNr, std::vector<Vector<>> &activations, const std::vector<Vector<>> &netInputs) const
	{
		activations[layerNr] = netInputs[layerNr];
	}


	void IdentityFunction::executeDerivation(const Vector<>& input, Vector<>& derivation) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("identity_function", "identity_deriv_assign", "identity_function.cl");
			executeVectorAssignKernel(kernel, input.getViennaclValue(), derivation.getViennaclValueForEditing());
		}
		else
		{
			AbstractActivationFunction::executeDerivation(input, derivation);
		}
	}


	double IdentityFunction::executeDerivation(double input) const
	{
		return 1;
	}

	AbstractCloneable* IdentityFunction::clone() const
	{
		return new IdentityFunction(*this);
	}


	double IdentityFunction::getMaximum() const
	{
		throw std::logic_error("A IdentityFunction does not have a maximum");
	}

	double IdentityFunction::getMinimum() const
	{
		throw std::logic_error("A IdentityFunction does not have a maximum");
	}

	bool IdentityFunction::hasAMaxAndMinimum() const
	{
		return false;
	}
}
