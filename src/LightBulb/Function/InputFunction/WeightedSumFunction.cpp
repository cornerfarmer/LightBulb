// Includes
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	void WeightedSumFunction::execute(int layerNr, const std::vector<Vector<>> &activations, std::vector<Vector<>> &netInputs, const std::vector<Matrix<>> &weights, const Vector<>* alternativeActivation) const
	{
		const Vector<>* activationToUse = alternativeActivation ? alternativeActivation : &activations[layerNr - 1];
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("weight_sum_function", "execute", "weight_sum_function.cl");

			/*kernel.global_work_size(0, activationToUse->getViennaclValue().size());
			kernel.global_work_size(1, 32);
			kernel.local_work_size(0, 8);
			kernel.local_work_size(1, 32);*/
			viennacl::ocl::enqueue(kernel(
				viennacl::traits::opencl_handle(activationToUse->getViennaclValue()),
				cl_uint(viennacl::traits::start(activationToUse->getViennaclValue())),
				cl_uint(viennacl::traits::stride(activationToUse->getViennaclValue())),
				cl_uint(viennacl::traits::size(activationToUse->getViennaclValue())),

				viennacl::traits::opencl_handle(netInputs[layerNr].getViennaclValueForEditing()),
				cl_uint(viennacl::traits::start(netInputs[layerNr].getViennaclValueForEditing())),
				cl_uint(viennacl::traits::stride(netInputs[layerNr].getViennaclValueForEditing())),
				cl_uint(viennacl::traits::size(netInputs[layerNr].getViennaclValueForEditing())),

				viennacl::traits::opencl_handle(weights[layerNr - 1].getViennaclValue()),
				cl_uint(viennacl::traits::start1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::start2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::stride1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::stride2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::size1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::size2(weights[layerNr - 1].getViennaclValue())),
				cl_uint(viennacl::traits::internal_size1(weights[layerNr - 1].getViennaclValue())), cl_uint(viennacl::traits::internal_size2(weights[layerNr - 1].getViennaclValue())),

				viennacl::ocl::local_mem(sizeof(float) * kernel.local_work_size(0) )
			));

		}
		else
			netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue() * activationToUse->getEigenValue();
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction(*this);
	}
}
