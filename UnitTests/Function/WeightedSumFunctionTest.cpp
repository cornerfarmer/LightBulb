#include "gtest/gtest.h"
#include "Function/WeightedSumFunction.hpp"

TEST(WeightedSumFunction, computeNetInputs)
{
	WeightedSumFunction function;
	// 2 - 3 - 1 Network:
	std::vector<Eigen::VectorXd> activations(3);
	activations[0] = Eigen::VectorXd(3);
	activations[0] << 1, 2, 1;
	activations[1] = Eigen::VectorXd(4);
	activations[1] << 1, 2, 3, 1;
	activations[2] = Eigen::VectorXd(1);

	std::vector<Eigen::VectorXd> netInputs(3);
	netInputs[0] = Eigen::VectorXd(2);
	netInputs[1] = Eigen::VectorXd(3);
	netInputs[2] = Eigen::VectorXd(1);

	std::vector<Eigen::MatrixXd> weights(2);
	weights[0] = Eigen::MatrixXd(3, 3);
	weights[0] << 1, 2, 3,
				4, 5, 6,
				7, 8, 9;				
	weights[1] = Eigen::MatrixXd(1, 4);
	weights[1] << 1, 2, 3, 4;

	function.execute(1, activations, netInputs, weights);
	function.execute(2, activations, netInputs, weights);

	std::vector<Eigen::VectorXd> expectedNetInputs(3);
	expectedNetInputs[1] = Eigen::VectorXd(3);
	expectedNetInputs[1] << 8, 20, 32;
	expectedNetInputs[2] = Eigen::VectorXd(1);
	expectedNetInputs[2] << 18;

	ASSERT_TRUE(netInputs[1].isApprox(expectedNetInputs[1]));
	ASSERT_TRUE(netInputs[2].isApprox(expectedNetInputs[2]));
}
