#pragma once

#ifndef _KERNELHELPER_H_
#define _KERNELHELPER_H_

#include <viennacl/ocl/kernel.hpp>
#include <viennacl/ocl/context.hpp>
#include <viennacl/traits/start.hpp>
#include <viennacl/traits/stride.hpp>
#include <viennacl/traits/size.hpp>
#include <viennacl/traits/handle.hpp>

inline viennacl::ocl::kernel& getKernel(std::string programName, std::string kernelName, std::string fileName)
{
	static std::map<std::string, bool> init;
	if (!init[programName]) {
		std::ifstream ifs("cl/" + fileName);
		std::string code((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

		viennacl::ocl::current_context().add_program(code, programName);
		init[programName] = true;
	}

	return viennacl::ocl::current_context().get_program(programName).get_kernel(kernelName);
}


inline void executeVectorAssignKernel(viennacl::ocl::kernel& kernel, const viennacl::vector_base<float>& in, viennacl::vector_base<float>& out)
{
	viennacl::ocl::packed_cl_uint size_vec1;
	size_vec1.start = cl_uint(viennacl::traits::start(out));
	size_vec1.stride = cl_uint(viennacl::traits::stride(out));
	size_vec1.size = cl_uint(viennacl::traits::size(out));
	size_vec1.internal_size = cl_uint(viennacl::traits::internal_size(out));

	viennacl::ocl::packed_cl_uint size_vec2;
	size_vec2.start = cl_uint(viennacl::traits::start(in));
	size_vec2.stride = cl_uint(viennacl::traits::stride(in));
	size_vec2.size = cl_uint(viennacl::traits::size(in));
	size_vec2.internal_size = cl_uint(viennacl::traits::internal_size(in));

	viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(out),
		size_vec1,
		viennacl::traits::opencl_handle(in),
		size_vec2)
	);
}

#endif
