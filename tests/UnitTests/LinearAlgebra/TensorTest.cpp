#include "LightBulb/LinearAlgebra/Tensor.hpp"
#include "gtest/gtest.h"

using namespace LightBulb;

TEST(Tensor, basicDataStorage)
{
	Tensor<> A(16, 16, 16);

	for (int m = 0; m < A.getEigenValue().size(); m++)
	{
		for (int r = 0; r < A.getEigenValue()[m].rows(); r++)
		{
			for (int c = 0; c < A.getEigenValue()[m].cols(); c++)
			{
				A.getEigenValueForEditing()[m](r, c) = m + r + c;
			}
		}
	}

	A.getViennaclValue();

	ASSERT_EQ(1, A.getViennaclValue()(1, 0));
	ASSERT_EQ(1, A.getViennaclValue()(16, 0));
	ASSERT_EQ(6, A.getViennaclValue()(33, 3));
	ASSERT_EQ(15 * 3, A.getViennaclValue()(16 * 16 - 1, 15));

	A.getViennaclValueForEditing()(1, 0) = 1;
	A.getViennaclValueForEditing()(16, 0) = 2;
	A.getViennaclValueForEditing()(33, 3) = 3;
	A.getViennaclValueForEditing()(16 * 16 - 1, 15) = 4;

	ASSERT_EQ(1, A.getViennaclValue()(1, 0));
	ASSERT_EQ(2, A.getViennaclValue()(16, 0));
	ASSERT_EQ(3, A.getViennaclValue()(33, 3));
	ASSERT_EQ(4, A.getViennaclValue()(16 * 16 - 1, 15));
}
