// Includes
#include "LightBulb/Random/ZigguratGenerator.hpp"
#include "LightBulb/Lib/ziggurat.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

namespace LightBulb
{
	ZigguratGenerator::ZigguratGenerator(int seed)
		:AbstractRandomGenerator(seed), fn(128), kn(128), wn(129)
	{
		ZigguratGenerator::reset();
		r4NorKernel.reset(new Kernel("ziggurat_generator", "r4_nor"));
		r4NorSetupKernel.reset(new Kernel("ziggurat_generator", "r4_nor_setup"));
	}

	ZigguratGenerator::~ZigguratGenerator() = default;

	float ZigguratGenerator::randFloat()
	{
		if (isCalculatorType(CT_GPU)) {
			Scalar<> output;
			output.getViennaclValueForEditing() = 0;

			viennacl::ocl::enqueue(r4NorKernel->use()(
				viennacl::traits::opencl_handle(state.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(kn.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(fn.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(wn.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(output.getViennaclValueForEditing()),
				cl_uint(0)
			));

			return output.getEigenValue();
		}
		else
		{
			return r4_nor(state.getEigenValueForEditing(), kn.getEigenValueForEditing().data(), fn.getEigenValueForEditing().data(), wn.getEigenValueForEditing().data());
		}
	}

	const Vector<>& ZigguratGenerator::randMultipleDouble(int count)
	{
		if (isCalculatorType(CT_GPU)) 
		{
			if (count > randomNumberCache.getViennaclValue().size())
				randomNumberCache.getViennaclValueForEditing().resize(count);

			for (int i = 0; i < count; i++) {
				viennacl::ocl::enqueue(r4NorKernel->use()(
					viennacl::traits::opencl_handle(state.getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(kn.getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(fn.getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(wn.getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(randomNumberCache.getViennaclValueForEditing()),
					cl_uint(i)
				));
			}

			return randomNumberCache;
		} 
		else
		{
			return AbstractRandomGenerator::randMultipleDouble(count);
		}
	}


	void ZigguratGenerator::reset()
	{
		if (isCalculatorType(CT_GPU)) 
		{
			state.getViennaclValueForEditing() = seed;

			viennacl::ocl::enqueue(r4NorSetupKernel->use()(
				viennacl::traits::opencl_handle(kn.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(fn.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(wn.getViennaclValueForEditing())
			));
		}
		else
		{
			state.getEigenValueForEditing() = seed;
			r4_nor_setup(kn.getEigenValueForEditing().data(), fn.getEigenValueForEditing().data(), wn.getEigenValueForEditing().data());
		}
	}
}
