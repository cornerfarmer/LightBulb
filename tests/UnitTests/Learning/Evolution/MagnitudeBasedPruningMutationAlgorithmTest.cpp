#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include "LightBulb/LinearAlgebra/Matrix.hpp"

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
	MockIndividual individual;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(individual, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Matrix<>> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	std::vector<unsigned int> neuronCounts(2, 2);
	EXPECT_CALL(networkTopology, getNeuronCountsPerLayer()).WillRepeatedly(testing::ReturnRef(neuronCounts));

	weights.push_back(Matrix<>(2, 3));
	weights[0].getEigenValueForEditing()(0, 0) = 1;
	weights[0].getEigenValueForEditing()(0, 1) = -2;
	weights[0].getEigenValueForEditing()(0, 2) = -10;
	weights[0].getEigenValueForEditing()(1, 0) = 0;
	weights[0].getEigenValueForEditing()(1, 1) = 5;
	weights[0].getEigenValueForEditing()(1, 2) = 3;
	weights.push_back(Matrix<>(1, 1));
	weights[1].getEigenValueForEditing()(0, 0) = 10;

	EXPECT_CALL(individual, removeNeuron(0, 1)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(individual);
}

TEST_F(MagnitudeBasedPruningMutationAlgorithmTest, removeNeuronByWeightCount)
{
	magnitudeBasedPruningMutationAlgorithm = new MagnitudeBasedPruningMutationAlgorithm(1, 0, false, false, false);
	MockIndividual individual;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(individual, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Matrix<>> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(testing::_, testing::_, testing::_)).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 2, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 1)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(1, 0, 0)).WillRepeatedly(testing::Return(false));
	std::vector<unsigned int> neuronCounts(2, 2);
	EXPECT_CALL(networkTopology, getNeuronCountsPerLayer()).WillRepeatedly(testing::ReturnRef(neuronCounts));

	weights.push_back(Matrix<>(2, 3));
	weights[0].getEigenValueForEditing()(0, 0) = 0;
	weights[0].getEigenValueForEditing()(0, 1) = -2;
	weights[0].getEigenValueForEditing()(0, 2) = 0;
	weights[0].getEigenValueForEditing()(1, 0) = 0;
	weights[0].getEigenValueForEditing()(1, 1) = 5;
	weights[0].getEigenValueForEditing()(1, 2) = 3;
	weights.push_back(Matrix<>(1, 1));
	weights[1].getEigenValueForEditing()(0, 0) = 0;

	EXPECT_CALL(individual, removeNeuron(0, 2)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(individual);
}


TEST_F(MagnitudeBasedPruningMutationAlgorithmTest, removeWeight)
{
	magnitudeBasedPruningMutationAlgorithm = new MagnitudeBasedPruningMutationAlgorithm(0, 1);
	MockIndividual individual;

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(individual, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Matrix<>> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(testing::_, testing::_, testing::_)).WillRepeatedly(testing::Return(true));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 2, 0)).WillRepeatedly(testing::Return(false));
	EXPECT_CALL(networkTopology, existsAfferentWeight(0, 0, 1)).WillRepeatedly(testing::Return(false));

	weights.push_back(Matrix<>(2, 3));
	weights[0].getEigenValueForEditing()(0, 0) = 0;
	weights[0].getEigenValueForEditing()(0, 1) = -0.4;
	weights[0].getEigenValueForEditing()(0, 2) = 0;
	weights[0].getEigenValueForEditing()(1, 0) = 0;
	weights[0].getEigenValueForEditing()(1, 1) = 1;
	weights[0].getEigenValueForEditing()(1, 2) = 4;
	weights.push_back(Matrix<>(1, 1));
	weights[1].getEigenValueForEditing()(0, 0) = -2;

	EXPECT_CALL(networkTopology, removeAfferentWeight(0, 1, 0)).Times(1);

	magnitudeBasedPruningMutationAlgorithm->execute(individual);
}
