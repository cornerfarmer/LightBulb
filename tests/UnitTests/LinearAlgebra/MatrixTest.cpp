#include "gtest/gtest.h"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

using namespace LightBulb;

TEST(Matrix, basicCompute)
{
	Matrix A(1024, 1024);
	Matrix B(1024, 1024);
	Matrix C(1024, 1024);

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
