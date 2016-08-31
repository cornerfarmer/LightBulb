#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>

class MutationAlgorithmTest : public testing::Test {
public:
	MutationAlgorithm* mutationAlgorithm;

	void SetUp() {
		mutationAlgorithm = new MutationAlgorithm(1.6);
	}

	virtual ~MutationAlgorithmTest()
	{
		delete mutationAlgorithm;
	}
};

TEST_F(MutationAlgorithmTest, execute)
{
	MockEvolutionObject object;

	std::vector<double> mutationStrength;
	mutationStrength.push_back(2);
	mutationStrength.push_back(-5);
	mutationStrength.push_back(0);
	mutationStrength.push_back(7500000);
	mutationStrength.push_back(-1000000);
	EXPECT_CALL(object, getMutationStrength()).WillRepeatedly(testing::Return(&mutationStrength));

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(object, getNeuralNetwork()).WillRepeatedly(testing::Return(&neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::Return(&networkTopology));
	std::vector<Eigen::MatrixXd> weights;
	EXPECT_CALL(networkTopology, getWeights()).WillRepeatedly(testing::Return(&weights));

	weights.push_back(Eigen::MatrixXd(2,2));
	weights[0](0, 0) = 2;
	weights[0](0, 1) = 1;
	weights[0](1, 0) = -5;
	weights[0](1, 1) = 0.1;
	weights.push_back(Eigen::MatrixXd(1, 1));
	weights[1](0, 0) = 10;

	mutationAlgorithm->execute(&object);

	EXPECT_NEAR(0.231262, mutationStrength[0], 0.00001);
	EXPECT_NEAR(-8.35703, mutationStrength[1], 0.00001);
	EXPECT_NEAR(0.000001f, mutationStrength[2], 0.00001);
	EXPECT_NEAR(50, mutationStrength[3], 0.00001);
	EXPECT_NEAR(-50, mutationStrength[4], 0.00001);

	EXPECT_NEAR(1.826609, weights[0](0, 0), 0.00001);
	EXPECT_NEAR(23.00891, weights[0](0, 1), 0.00001);
	EXPECT_NEAR(-5.00000, weights[0](1, 0), 0.00001);
	EXPECT_NEAR(-44.92901, weights[0](1, 1), 0.00001);
	EXPECT_NEAR(37.36058, weights[1](0, 0), 0.00001);
}
