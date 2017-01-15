// Includes
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
// Library includes
#include <math.h>
#include <limits>
#include <stdexcept>
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include <viennacl/vector_proxy.hpp>
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	FermiFunction::FermiFunction(double temperatureParameter_)
	{
		temperatureParameter = temperatureParameter_;
	}

	double FermiFunction::execute(double input) const
	{
		// Execture the fermi function
		return  1 / (1 + exp(-input / temperatureParameter));
	}

	double FermiFunction::executeDerivation(double input) const
	{
		// Execute the derivation of the Fermi function		
		return execute(input) * (1 - execute(input));
	}

	AbstractCloneable* FermiFunction::clone() const
	{
		return new FermiFunction(*this);
	}

	double FermiFunction::getMaximum() const
	{
		return 1;
	}

	double FermiFunction::getMinimum() const
	{
		return 0;
	}

	bool FermiFunction::hasAMaxAndMinimum() const
	{
		return true;
	}

	void FermiFunction::execute(int layerNr, std::vector<Vector>& activations, const std::vector<Vector>& netInputs) const
	{
		if (isCalculatorType(CT_GPU)) 
		{
			viennacl::range r(0, activations[layerNr].getViennaclValue().size() - 1);
			viennacl::vector_range<viennacl::vector<float>> v_sub(activations[layerNr].getViennaclValueForEditing(), r);
			static viennacl::ocl::kernel& kernel = getKernel("fermi", "fermi_assign", "fermi.cl");
			executeVectorAssignKernel(kernel, netInputs[layerNr].getViennaclValue(), v_sub);
		} 
		else
		{
			AbstractActivationFunction::execute(layerNr, activations, netInputs);
		}
	}


	void FermiFunction::executeDerivation(const Vector& input, Vector& derivation) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("fermi", "fermi_deriv_assign", "fermi.cl");
			executeVectorAssignKernel(kernel, input.getViennaclValue(), derivation.getViennaclValueForEditing());
		}
		else
		{
			AbstractActivationFunction::executeDerivation(input, derivation);
		}
	}


}
