// Includes
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

namespace LightBulb
{
	WeightedSumFunction::WeightedSumFunction()
	{
		executeKernel.reset(new Kernel("weight_sum_function", "execute"));
	}

	WeightedSumFunction::~WeightedSumFunction() = default;

	void WeightedSumFunction::execute(int layerNr, const std::vector<Vector<>> &activations, std::vector<Vector<>> &netInputs, const std::vector<Matrix<>> &weights, const Vector<>* alternativeActivation) const
	{
		const Vector<>* activationToUse = alternativeActivation ? alternativeActivation : &activations[layerNr - 1];
		if (isCalculatorType(CT_GPU))
		{
			/*kernel.global_work_size(0, activationToUse->getViennaclValue().size());
			kernel.global_work_size(1, 32);
			kernel.local_work_size(0, 8);
			kernel.local_work_size(1, 32);*/
			viennacl::ocl::enqueue(executeKernel->use()(
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

				viennacl::ocl::local_mem(sizeof(float) * executeKernel->use().local_work_size(0))
			));

		}
		else
		{
			if (activationToUse->getEigenValue().rows() != weights[layerNr - 1].getEigenValue().cols())
			{
				netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue().leftCols(activationToUse->getEigenValue().rows()) * activationToUse->getEigenValue();
				netInputs[layerNr].getEigenValueForEditing().noalias() += weights[layerNr - 1].getEigenValue().col(activationToUse->getEigenValue().rows());
			}
			else
				netInputs[layerNr].getEigenValueForEditing().noalias() = weights[layerNr - 1].getEigenValue() * activationToUse->getEigenValue();
		}
	}

	AbstractCloneable* WeightedSumFunction::clone() const
	{
		return new WeightedSumFunction();
	}
}
