// Includes
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

// Library includes

namespace LightBulb
{
	RectifierFunction::RectifierFunction(double leakyFac_)
	{
		leakyFac = leakyFac_;
	}

	double RectifierFunction::execute(double input) const
	{
		// Execture the fermi function
		return  std::max(leakyFac * input, input);
	}

	void RectifierFunction::execute(int layerNr, std::vector<Vector<>> &activations, const std::vector<Vector<>> &netInputs) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("rectifier_function", "rectifier_assign", "rectifier_function.cl");
			executeVectorAssignKernel(kernel, netInputs[layerNr].getViennaclValue(), activations[layerNr].getViennaclValueForEditing());
		}
		else
		{
			activations[layerNr].getEigenValueForEditing().topRows(netInputs[layerNr].getEigenValue().size()) = netInputs[layerNr].getEigenValue().cwiseMax(0);
		}
	}

	void RectifierFunction::executeDerivation(const Vector<>& input, Vector<>& derivation) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("rectifier_function", "rectifier_deriv_assign", "rectifier_function.cl");
			executeVectorAssignKernel(kernel, input.getViennaclValue(), derivation.getViennaclValueForEditing());
		}
		else
		{
			AbstractActivationFunction::executeDerivation(input, derivation);
		}
	}


	double RectifierFunction::executeDerivation(double input) const
	{
		// Execute the derivation of the Fermi function		
		return (input > 0);
	}

	AbstractCloneable* RectifierFunction::clone() const
	{
		return new RectifierFunction(*this);
	}

	double RectifierFunction::getMaximum() const
	{
		return 1;
	}

	double RectifierFunction::getMinimum() const
	{
		return 0;
	}

	bool RectifierFunction::hasAMaxAndMinimum() const
	{
		return false;
	}

}
