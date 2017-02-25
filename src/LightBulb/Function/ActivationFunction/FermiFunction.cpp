// Includes
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
// Library includes
#include <math.h>
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

namespace LightBulb
{
	FermiFunction::FermiFunction(double temperatureParameter_)
	{
		temperatureParameter = temperatureParameter_;
		fermiAssignKernel.reset(new Kernel("fermi", "fermi_assign"));
		fermiDerivAssignKernel.reset(new Kernel("fermi", "fermi_deriv_assign"));
	}

	FermiFunction::~FermiFunction() = default;

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
		return new FermiFunction(temperatureParameter);
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

	void FermiFunction::execute(int layerNr, std::vector<Vector<>>& activations, const std::vector<Vector<>>& netInputs) const
	{
		if (isCalculatorType(CT_GPU)) 
		{
			executeVectorAssignKernel(fermiAssignKernel->use(), netInputs[layerNr].getViennaclValue(), activations[layerNr].getViennaclValueForEditing());
		} 
		else
		{
			AbstractActivationFunction::execute(layerNr, activations, netInputs);
		}
	}


	void FermiFunction::executeDerivation(const Vector<>& input, Vector<>& derivation) const
	{
		if (isCalculatorType(CT_GPU))
		{
			executeVectorAssignKernel(fermiDerivAssignKernel->use(), input.getViennaclValue(), derivation.getViennaclValueForEditing());
		}
		else
		{
			AbstractActivationFunction::executeDerivation(input, derivation);
		}
	}


}
