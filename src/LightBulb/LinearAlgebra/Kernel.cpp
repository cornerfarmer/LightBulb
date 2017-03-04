// Includes
#include "LightBulb/LinearAlgebra/Kernel.hpp"
#include <viennacl/ocl/kernel.hpp>
#include <viennacl/ocl/context.hpp>
#include <viennacl/ocl/backend.hpp>

LightBulb::Kernel::Kernel(std::string programName_, std::string kernelName_)
{
	programName = programName_;
	kernelName = kernelName_;
	kernel = nullptr;
}

viennacl::ocl::kernel& LightBulb::Kernel::use() const
{
	if (!kernel) 
	{
		if (!viennacl::ocl::current_context().has_program("cl/" + programName + ".cl"))
		{
			std::ifstream ifs("cl/" + programName + ".cl");
			std::string code((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

			viennacl::ocl::current_context().add_program(code, programName);
		}

		kernel = &viennacl::ocl::current_context().get_program(programName).get_kernel(kernelName);
	}
	return *kernel;
}
