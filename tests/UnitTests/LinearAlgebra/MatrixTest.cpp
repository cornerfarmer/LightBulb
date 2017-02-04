#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "gtest/gtest.h"

using namespace LightBulb;

TEST(Matrix, basicCompute)
{
	Matrix<> A(1024, 1024);
	Matrix<> B(1024, 1024);
	Matrix<> C(1024, 1024);

	for (int r = 0; r < A.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < A.getEigenValue().cols(); c++)
		{
			A.getEigenValueForEditing()(r, c) = 0.5;
			B.getEigenValueForEditing()(r, c) = 0.25;
		}
	}

	C.getViennaclValueForEditing() = viennacl::linalg::prod(A.getViennaclValue(), B.getViennaclValue());

	for (int r = 0; r < C.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < C.getEigenValue().cols(); c++)
		{
			EXPECT_EQ(128, C.getEigenValue()(r, c));
		}
	}
}


TEST(Matrix, assignOperatorTest)
{
	Matrix<> A(1024, 1024);
	Matrix<> B(1024, 1024);

	for (int r = 0; r < A.getEigenValue().rows(); r++)
	{
		for (int c = 0; c < A.getEigenValue().cols(); c++)
		{
			A.getEigenValueForEditing()(r, c) = 0.5;
		}
	}

	B.getViennaclValue();

	A = B;

	EXPECT_EQ(A, B);
}

TEST(Matrix, performanceTest)
{
	viennacl::vector<float> testMatrix(1024);
	viennacl::scalar<float> sum = 0;
	testMatrix = viennacl::scalar_vector<float>(1024, 1);

	auto& test1 = getKernel("test", "test1", "test.cl");
	clock_t begin = clock();
	for (int i = 0; i < 100000; i++) {
		viennacl::ocl::enqueue(test1(cl_uint(1),
			cl_uint(2),
			cl_uint(3),
			cl_uint(4),
			cl_uint(5),
			cl_uint(6))
		);
	}
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	viennacl::backend::finish();


	auto& test2 = getKernel("test", "test2", "test.cl");
	begin = clock();
	for (int i = 0; i < 100000; i++) {
		viennacl::ocl::enqueue(test2(cl_uint(1))
		);
	}
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	viennacl::backend::finish();

	auto& test3 = getKernel("test", "test3", "test.cl");
	test3.global_work_size(1, 1);
	begin = clock();
	for (int i = 0; i < 100000; i++) {
		//viennacl::ocl::enqueue(test3(viennacl::traits::opencl_handle(testMatrix), viennacl::traits::opencl_handle(sum))
		testMatrix = viennacl::scalar_vector<float>(1024, 1);
		//);
	}
	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time << ";" << (end - begin) << std::endl;

	viennacl::backend::finish();
	std::cout << sum << std::endl;
}
