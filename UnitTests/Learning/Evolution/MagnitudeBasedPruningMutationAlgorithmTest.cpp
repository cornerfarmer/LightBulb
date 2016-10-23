#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>

using namespace LightBulb;

class MagnitudeBasedPruningMutationAlgorithmTest : public testing::Test {
public:
	MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm;

	void SetUp() {
		
	}

	virtual ~MagnitudeBasedPruningMutationAlgorithmTest()
	{
		delete magnitudeBasedPruningMutationAlgorithm;
	}
};

TEST_F(MagnitudeBasedPruningMutationAlgorithmTest, removeNeuronByWeightSum)
{
	magnitudeBasedPruningMutationAlgorithm = new MagnitudeBasedPruningMutationAlgorithm(1, 0, false, false, true);
	MockEvolutionObject object;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(object, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Eigen::MatrixXd> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	std::vector<unsigned int> neuronCounts(2, 2);
	EXPECT_CALL(networkTopology, getNeuronCountsPerLayer()).WillRepeatedly(testing::ReturnRef(neuronCounts));

	weights.push_back(Eigen::MatrixXd(2, 3));
	weights[0](0, 0) = 1;
	weights[0](0, 1) = -2;
	weights[0](0, 2) = -10;
	weights[0](1, 0) = 0;
	weights[0](1, 1) = 5;
	weights[0](1, 2) = 3;
	weights.push_back(Eigen::MatrixXd(1, 1));
	weights[1](0, 0) = 10;

	EXPECT_CALL(networkTopology, removeNeuron(0, 1)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(object);
}

TEST_F(MagnitudeBasedPruningMutationAlgorithmTest, removeNeuronByWeightCount)
{
	magnitudeBasedPruningMutationAlgorithm = new MagnitudeBasedPruningMutationAlgorithm(1, 0, false, false, false);
	MockEvolutionObject object;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(object, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Eigen::MatrixXd> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(testing::_, testing::_, testing::_)).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 2, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 1)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(1, 0, 0)).WillRepeatedly(testing::Return(false));
	std::vector<unsigned int> neuronCounts(2, 2);
	EXPECT_CALL(networkTopology, getNeuronCountsPerLayer()).WillRepeatedly(testing::ReturnRef(neuronCounts));

	weights.push_back(Eigen::MatrixXd(2, 3));
	weights[0](0, 0) = 0;
	weights[0](0, 1) = -2;
	weights[0](0, 2) = 0;
	weights[0](1, 0) = 0;
	weights[0](1, 1) = 5;
	weights[0](1, 2) = 3;
	weights.push_back(Eigen::MatrixXd(1, 1));
	weights[1](0, 0) = 0;

	EXPECT_CALL(networkTopology, removeNeuron(0, 2)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(object);
}


TEST_F(MagnitudeBasedPruningMutationAlgorithmTest, removeWeight)
{
	magnitudeBasedPruningMutationAlgorithm = new MagnitudeBasedPruningMutationAlgorithm(0, 1);
	MockEvolutionObject object;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(object, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Eigen::MatrixXd> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(testing::_, testing::_, testing::_)).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 2, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 1)).WillRepeatedly(testing::Return(false));

	weights.push_back(Eigen::MatrixXd(2, 3));
	weights[0](0, 0) = 0;
	weights[0](0, 1) = -0.4;
	weights[0](0, 2) = 0;
	weights[0](1, 0) = 0;
	weights[0](1, 1) = 1;
	weights[0](1, 2) = 4;
	weights.push_back(Eigen::MatrixXd(1, 1));
	weights[1](0, 0) = -2;

	EXPECT_CALL(networkTopology, removeAfferentWeight(0, 1, 0)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(object);
}
