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
		viennacl::range r(0, activations[layerNr].getViennaclValue().size() - 1);
		viennacl::vector_range<viennacl::vector<float>> v_sub(activations[layerNr].getViennaclValueForEditing(), r);
		internExecute(netInputs[layerNr].getViennaclValue(), v_sub);
	}

	template<typename T>
	viennacl::vector_expression<const viennacl::vector_base<T>, const viennacl::vector_base<T>, viennacl::op_element_unary<viennacl::op_fermi>> FermiFunction::executeOpenCL(viennacl::vector_base<T> const & v) const
	{
		return viennacl::vector_expression<const viennacl::vector_base<T>, const viennacl::vector_base<T>, viennacl::op_element_unary<viennacl::op_fermi>>(v, v);
	}

	void FermiFunction::internExecute(const viennacl::vector_base<float>& in, viennacl::vector_base<float>& out) const
	{
		executeVectorAssignKernel(getKernel("fermi", "fermi_assign", "fermi.cl"), in, out);
	}

	Vector FermiFunction::executeDerivation(const Vector& input) const
	{
		Vector derivation(input.getViennaclValue().size());
		executeVectorAssignKernel(getKernel("fermi", "fermi_deriv_assign", "fermi.cl"), input.getViennaclValue(), derivation.getViennaclValueForEditing());
		return derivation;
	}


}
