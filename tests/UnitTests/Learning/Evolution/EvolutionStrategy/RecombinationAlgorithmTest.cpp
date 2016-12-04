#include "gtest/gtest.h"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include "Mocks/MockRandomGenerator.hpp"

using namespace LightBulb;

class RecombinationAlgorithmTest : public testing::Test {
public:
	RecombinationAlgorithm* recombinationAlgorithm;
	MockIndividual individual1;
	MockIndividual individual2;
	std::vector<double> mutationStrength1, mutationStrength2;
	std::vector<Eigen::MatrixXd> weights1, weights2;
	MockNeuralNetwork neuralNetwork1, neuralNetwork2;
	MockNetworkTopology networkTopology1, networkTopology2;
	MockRandomGenerator mockRandomGenerator;
	void SetUp() {
		mutationStrength1.push_back(2);
		mutationStrength1.push_back(-5);
		EXPECT_CALL(individual1, getMutationStrength()).WillRepeatedly(testing::ReturnRef(mutationStrength1));
		
		
		EXPECT_CALL(individual1, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork1));
		EXPECT_CALL(neuralNetwork1, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology1));
		EXPECT_CALL(networkTopology1, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights1));

		weights1.push_back(Eigen::MatrixXd(1, 2));
		weights1[0](0, 0) = 2;
		weights1[0](0, 1) = -3;
		weights1.push_back(Eigen::MatrixXd(1, 1));
		weights1[1](0, 0) = 10;

				
		mutationStrength2.push_back(0.3);
		mutationStrength2.push_back(3);
		EXPECT_CALL(individual2, getMutationStrength()).WillRepeatedly(testing::ReturnRef(mutationStrength2));

		EXPECT_CALL(individual2, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork2));
		EXPECT_CALL(neuralNetwork2, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology2));
		EXPECT_CALL(networkTopology2, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights2));

		weights2.push_back(Eigen::MatrixXd(1, 2));
		weights2[0](0, 0) = -6;
		weights2[0](0, 1) = 1;
		weights2.push_back(Eigen::MatrixXd(1, 1));
		weights2[1](0, 0) = 3;
	}

	void addExtraNeuronsForDifferentSizes()
	{
		weights1[0] = Eigen::MatrixXd(2, 3);
		weights1[0](0, 0) = 2;
		weights1[0](0, 1) = -3;
		weights1[0](0, 2) = 5;
		weights1[0](1, 0) = -2;
		weights1[0](1, 1) = 3;
		weights1[0](1, 2) = -5;

		weights1[1] = Eigen::MatrixXd(1, 2);
		weights1[1](0, 0) = 10;
		weights1[1](0, 1) = -1;

		mutationStrength1.push_back(0.1);

		weights2[1] = Eigen::MatrixXd(2, 1);
		weights2[1](0, 0) = 3;
		weights2[1](1, 0) = 6;

	}

	virtual ~RecombinationAlgorithmTest()
	{
		delete recombinationAlgorithm;
	}
};

TEST_F(RecombinationAlgorithmTest, executeWithAverage)
{
	recombinationAlgorithm = new RecombinationAlgorithm(true, true);
	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(1.15, mutationStrength1[0], 0.00001);
	EXPECT_NEAR(-1, mutationStrength1[1], 0.00001);

	EXPECT_NEAR(-2, weights1[0](0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[0](0, 1), 0.00001);
	EXPECT_NEAR(6.5, weights1[1](0, 0), 0.00001);
}


TEST_F(RecombinationAlgorithmTest, executeWithoutAverage)
{
	recombinationAlgorithm = new RecombinationAlgorithm(false, false);

	recombinationAlgorithm->setRandomGenerator(mockRandomGenerator);
	testing::InSequence s;
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));

	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(0.3, mutationStrength1[0], 0.00001);
	EXPECT_NEAR(3, mutationStrength1[1], 0.00001);

	EXPECT_NEAR(2, weights1[0](0, 0), 0.00001);
	EXPECT_NEAR(1, weights1[0](0, 1), 0.00001);
	EXPECT_NEAR(10, weights1[1](0, 0), 0.00001);
}

TEST_F(RecombinationAlgorithmTest, executeWithAverageWithDifferentSizes)
{
	addExtraNeuronsForDifferentSizes();

	recombinationAlgorithm = new RecombinationAlgorithm(true, true);
	recombinationAlgorithm->execute(individual1, individual2);

	EXPECT_NEAR(1.15, mutationStrength1[0], 0.00001);
	EXPECT_NEAR(-1, mutationStrength1[1], 0.00001);
	EXPECT_NEAR(0.1, mutationStrength1[2], 0.00001);

	EXPECT_NEAR(-2, weights1[0](0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[0](0, 1), 0.00001);
	EXPECT_NEAR(5, weights1[0](0, 2), 0.00001);
	EXPECT_NEAR(-2, weights1[0](1, 0), 0.00001);
	EXPECT_NEAR(3, weights1[0](1, 1), 0.00001);
	EXPECT_NEAR(-5, weights1[0](1, 2), 0.00001);
	EXPECT_NEAR(6.5, weights1[1](0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[1](0, 1), 0.00001);
}


TEST_F(RecombinationAlgorithmTest, executeWithoutAverageWithDifferentSizes)
{
	srand(1);
	addExtraNeuronsForDifferentSizes();

	recombinationAlgorithm = new RecombinationAlgorithm(false, false);

	recombinationAlgorithm->setRandomGenerator(mockRandomGenerator);
	testing::InSequence s;
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockRandomGenerator, randDouble()).WillOnce(testing::Return(1));
	
	recombinationAlgorithm->execute(individual1, individual2);
	
	EXPECT_NEAR(0.3, mutationStrength1[0], 0.00001);
	EXPECT_NEAR(3, mutationStrength1[1], 0.00001);
	EXPECT_NEAR(0.1, mutationStrength1[2], 0.00001);

	EXPECT_NEAR(2, weights1[0](0, 0), 0.00001);
	EXPECT_NEAR(1, weights1[0](0, 1), 0.00001);
	EXPECT_NEAR(5, weights1[0](0, 2), 0.00001);
	EXPECT_NEAR(-2, weights1[0](1, 0), 0.00001);
	EXPECT_NEAR(3, weights1[0](1, 1), 0.00001);
	EXPECT_NEAR(-5, weights1[0](1, 2), 0.00001);
	EXPECT_NEAR(10, weights1[1](0, 0), 0.00001);
	EXPECT_NEAR(-1, weights1[1](0, 1), 0.00001);
}
