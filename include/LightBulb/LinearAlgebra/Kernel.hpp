#pragma once

#ifndef _KERNEL_H_
#define _KERNEL_H_

// Includes
#include <string>

namespace viennacl {
	namespace ocl {
		class kernel;
	}
}

namespace LightBulb
{
	class Kernel
	{
	protected:
		std::string programName;
		std::string kernelName;
		mutable viennacl::ocl::kernel* kernel;
	public:
		Kernel(std::string programName_, std::string kernelName_);
		//viennacl::ocl::kernel& use();
		viennacl::ocl::kernel& use() const;
	};

}

#endif