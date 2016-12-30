// Includes
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
// Library includes
#include <math.h>
#include <limits>
#include <stdexcept>
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include <viennacl/vector_proxy.hpp>

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


	void FermiFunction::internExecute(const viennacl::vector_base<float>& in, viennacl::vector_base<float>& out) const
	{
		out = viennacl::linalg::element_exp(-1 * in / temperatureParameter);
		viennacl::vector<float> ones = viennacl::scalar_vector<float>(out.size(), 1);
		out += ones;
		out = viennacl::linalg::element_div(ones, out);
	}

	Vector FermiFunction::executeDerivation(const Vector& input) const
	{
		Vector derivation;
		viennacl::vector<float> ones = viennacl::scalar_vector<float>(input.getViennaclValue().size(), 1);
		internExecute(input.getViennaclValue(), derivation.getViennaclValueForEditing());
		derivation.getViennaclValueForEditing() = viennacl::linalg::element_prod(derivation.getViennaclValue(), ones - derivation.getViennaclValue());
		return derivation;
	}


}
