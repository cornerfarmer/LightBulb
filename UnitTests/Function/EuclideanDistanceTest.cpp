#include "gtest/gtest.h"
#include "Function/InputFunction/EuclideanDistance.hpp"
#include <math.h>

using namespace LightBulb;

TEST(EuclideanDistance, computeNetInputs)
{
	EuclideanDistance function;
	// 2 - 3 - 1 Network:
	Eigen::VectorXd activations(8);
	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> activationsPerLayer;
	activationsPerLayer.push_back(std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), 0, 3)));
	*activationsPerLayer[0] << 1, 2, 1;
	activationsPerLayer.push_back(std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), 3, 4)));
	*activationsPerLayer[1] << 1, 2, 3, 1;
	activationsPerLayer.push_back(std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>(new Eigen::VectorBlock<Eigen::VectorXd>(activations.derived(), 7, 1)));

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

	function.execute(1, activationsPerLayer, netInputs, weights);
	function.execute(2, activationsPerLayer, netInputs, weights);

	std::vector<Eigen::VectorXd> expectedNetInputs(3);
	expectedNetInputs[1] = Eigen::VectorXd(3);
	expectedNetInputs[1] << sqrt(4.0), sqrt(43.0), sqrt(136.0);
	expectedNetInputs[2] = Eigen::VectorXd(1);
	expectedNetInputs[2] << sqrt(9.0);

	ASSERT_TRUE(netInputs[1].isApprox(expectedNetInputs[1]));
	ASSERT_TRUE(netInputs[2].isApprox(expectedNetInputs[2]));
}
