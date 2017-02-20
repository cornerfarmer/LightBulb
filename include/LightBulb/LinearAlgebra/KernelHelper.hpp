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

inline void copyMatrixToTensorArea(viennacl::matrix_base<float>& tensor, const viennacl::matrix_base<float>& matrix, int area)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_matrix_to_tensor_area", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(matrix),
		viennacl::traits::size1(matrix),
		viennacl::traits::size2(matrix),
		viennacl::traits::internal_size2(matrix),
		viennacl::traits::opencl_handle(tensor),
		viennacl::traits::internal_size2(tensor),
		cl_uint(area)
	));
}

inline void copyMatrixToTensorArea(viennacl::matrix_base<float>& tensor, const viennacl::matrix_base<float>& matrix, const viennacl::scalar<int>& area)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_matrix_to_tensor_area_scalar", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(matrix),
		viennacl::traits::size1(matrix),
		viennacl::traits::size2(matrix),
		viennacl::traits::internal_size2(matrix),
		viennacl::traits::opencl_handle(tensor),
		viennacl::traits::internal_size2(tensor),
		viennacl::traits::opencl_handle(area)
	));
}


inline void copyVectorToMatrixCol(viennacl::matrix_base<float>& matrix, const viennacl::vector_base<float>& vector, int column)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_vector_to_matrix_col", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::size(vector),
		viennacl::traits::opencl_handle(matrix),
		viennacl::traits::internal_size2(matrix),
		cl_uint(column)
	));
}

inline void copyVectorToMatrixCol(viennacl::matrix_base<float>& matrix, const viennacl::vector_base<float>& vector, const viennacl::scalar<int>& column)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_vector_to_matrix_col_scalar", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::size(vector),
		viennacl::traits::opencl_handle(matrix),
		viennacl::traits::internal_size2(matrix),
		viennacl::traits::opencl_handle(column)
	));
}

inline void copyScalarToVectorElement(viennacl::vector_base<float>& vector, const viennacl::scalar<float>& scalar, int element)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_scalar_to_vector_elem", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::opencl_handle(scalar),
		cl_uint(element)
	));
}

inline void copyScalarToVectorElement(viennacl::vector_base<float>& vector, const viennacl::scalar<float>& scalar, const viennacl::scalar<int>& element)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_scalar_to_vector_elem_scalar", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::opencl_handle(scalar),
		viennacl::traits::opencl_handle(element)
	));
}


inline void copyScalarToVectorElement(viennacl::vector_base<char>& vector, const viennacl::scalar<char>& scalar, int element)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_scalar_to_vector_elem_char", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::opencl_handle(scalar),
		cl_uint(element)
	));
}

inline void copyScalarToVectorElement(viennacl::vector_base<char>& vector, const viennacl::scalar<char>& scalar, const viennacl::scalar<int>& element)
{
	static viennacl::ocl::kernel& kernel = getKernel("standard_operations", "copy_scalar_to_vector_elem_char_scalar", "standard_operations.cl");

	viennacl::ocl::enqueue(kernel(
		viennacl::traits::opencl_handle(vector),
		viennacl::traits::opencl_handle(scalar),
		viennacl::traits::opencl_handle(element)
	));
}

#endif
