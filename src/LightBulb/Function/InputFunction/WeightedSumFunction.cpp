// Includes
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	void WeightedSumFunction::execute(int layerNr, const std::vector<Vector> &activations, std::vector<Vector> &netInputs, const std::vector<Matrix> &weights) const
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("weight_sum_function", "execute", "weight_sum_function.cl");

			viennacl::ocl::enqueue(kernel(
				viennacl::traits::opencl_handle(activations[layerNr - 1].getViennaclValue()),
				cl_uint(viennacl::traits::start(activations[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::stride(activations[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::size(activations[layerNr - 1].getViennaclValue())),

				viennacl::traits::opencl_handle(netInputs[layerNr].getViennaclValue()),
				cl_uint(viennacl::traits::start(netInputs[layerNr].getViennaclValue())),
				cl_uint(viennacl::traits::stride(netInputs[layerNr].getViennaclValue())),
				cl_uint(viennacl::traits::size(netInputs[layerNr].getViennaclValue())),

				viennacl::traits::opencl_handle(weights[layerNr - 1].getViennaclValue()),
				cl_uint(viennacl::traits::start1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::start2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::stride1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::stride2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::size1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::size2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::internal_size1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::internal_size2(weights[layerNr - 1].getViennaclValue())),

				viennacl::ocl::local_mem(sizeof(float) * kernel.local_work_size())
			));

		}
		else
			netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue() * activations[layerNr - 1].getEigenValue();
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction(*this);
	}
}
