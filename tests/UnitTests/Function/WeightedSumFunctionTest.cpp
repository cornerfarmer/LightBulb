#include "gtest/gtest.h"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

using namespace LightBulb;

TEST(WeightedSumFunction, computeNetInputs)
{
	WeightedSumFunction function;
	// 2 - 3 - 1 Network:
	std::vector<Vector<>> activations;
	activations.push_back(Vector<>(3));
	activations[0].getEigenValueForEditing() << 1, 2, 1;
	activations.push_back(Vector<>(4));
	activations[1].getEigenValueForEditing() << 1, 2, 3, 1;
	activations.push_back(Vector<>(1));

	std::vector<Vector<>> netInputs(3);
	netInputs[0] = Vector<>(2);
	netInputs[1] = Vector<>(3);
	netInputs[2] = Vector<>(1);

	std::vector<Matrix<>> weights(2);
	weights[0] = Matrix<>(3, 3);
	weights[0].getEigenValueForEditing() << 1, 2, 3,
				4, 5, 6,
				7, 8, 9;				
	weights[1] = Matrix<>(1, 4);
	weights[1].getEigenValueForEditing() << 1, 2, 3, 4;

	function.execute(1, activations, netInputs, weights);
	function.execute(2, activations, netInputs, weights);

	std::vector<Eigen::VectorXf> expectedNetInputs(3);
	expectedNetInputs[1] = Eigen::VectorXf(3);
	expectedNetInputs[1] << 8, 20, 32;
	expectedNetInputs[2] = Eigen::VectorXf(1);
	expectedNetInputs[2] << 18;

	ASSERT_TRUE(netInputs[1].getEigenValue().isApprox(expectedNetInputs[1]));
	ASSERT_TRUE(netInputs[2].getEigenValue().isApprox(expectedNetInputs[2]));
}
