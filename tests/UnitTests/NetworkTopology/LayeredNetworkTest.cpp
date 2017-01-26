#include "gtest/gtest.h"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

using namespace LightBulb;

class FeedForwardNetworkTopologyTest : public testing::Test {
public:
	FeedForwardNetworkTopology* network;
	void SetUp() {
		
	}

	FeedForwardNetworkTopologyOptions getDefaultOptions()
	{
		FeedForwardNetworkTopologyOptions options;
		options.neuronsPerLayerCount.push_back(2);
		options.neuronsPerLayerCount.push_back(3);
		options.neuronsPerLayerCount.push_back(1);
		options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
		return options;
	}

	virtual ~FeedForwardNetworkTopologyTest()
	{
		delete network;
	}
};

TEST_F(FeedForwardNetworkTopologyTest, createSimpleNetwork)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = network->getAllNetInputs();
	EXPECT_EQ(netInputs.size(), 3);
	EXPECT_EQ(netInputs[0].getEigenValue().rows(), 2);
	EXPECT_EQ(netInputs[1].getEigenValue().rows(), 3);
	EXPECT_EQ(netInputs[2].getEigenValue().rows(), 1);

	auto& activations = network->getAllActivations();
	EXPECT_EQ(activations.size(), 3);
	EXPECT_EQ(activations[0].getEigenValue().rows(), 3);
	EXPECT_EQ(activations[1].getEigenValue().rows(), 4);
	EXPECT_EQ(activations[2].getEigenValue().rows(), 2);

	auto& weights = network->getAllWeights();
	EXPECT_EQ(weights.size(), 2);
	EXPECT_EQ(weights[0].getEigenValue().rows(), 3);
	EXPECT_EQ(weights[0].getEigenValue().cols(), 3);
	EXPECT_EQ(weights[1].getEigenValue().rows(), 1);
	EXPECT_EQ(weights[1].getEigenValue().cols(), 4);
}


TEST_F(FeedForwardNetworkTopologyTest, createNetworkWithShortcuts)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	options.enableShortcuts = true;
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = network->getAllNetInputs();
	EXPECT_EQ(netInputs.size(), 3);
	EXPECT_EQ(netInputs[0].getEigenValue().rows(), 2);
	EXPECT_EQ(netInputs[1].getEigenValue().rows(), 3);
	EXPECT_EQ(netInputs[2].getEigenValue().rows(), 1);

	auto& activations = network->getAllActivations();
	EXPECT_EQ(activations.size(), 3);
	EXPECT_EQ(activations[0].getEigenValue().rows(), 3);
	EXPECT_EQ(activations[1].getEigenValue().rows(), 6);
	EXPECT_EQ(activations[2].getEigenValue().rows(), 7);

	auto& weights = network->getAllWeights();
	EXPECT_EQ(weights.size(), 2);
	EXPECT_EQ(weights[0].getEigenValue().rows(), 3);
	EXPECT_EQ(weights[0].getEigenValue().cols(), 3);
	EXPECT_EQ(weights[1].getEigenValue().rows(), 1);
	EXPECT_EQ(weights[1].getEigenValue().cols(), 6);
}


TEST_F(FeedForwardNetworkTopologyTest, addNeuron)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	netInputs[0].getEigenValueForEditing() << 1, 2;
	netInputs[1].getEigenValueForEditing() << 1, 2, 3;
	netInputs[2].getEigenValueForEditing() << 1;

	auto& activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	activations[0].getEigenValueForEditing().col(0) << 1, 2, 3;
	activations[1].getEigenValueForEditing().col(0) << 1, 2, 3, 4;
	activations[2].getEigenValueForEditing().col(0) << 1, 2;

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 1, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 5, 6,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4;

	network->addNeuron(0);
	network->addNeuron(1);
	network->addNeuron(1);
	network->addNeuron(2);
	network->addNeuron(2);
	network->addNeuron(2);

	std::vector<Vector<>> expectedNetInputs;
	expectedNetInputs.push_back(Vector<>(3));
	expectedNetInputs.push_back(Vector<>(5));
	expectedNetInputs.push_back(Vector<>(4));
	expectedNetInputs[0].getEigenValueForEditing() << 1, 2, 0;
	expectedNetInputs[1].getEigenValueForEditing() << 1, 2, 3, 0, 0;
	expectedNetInputs[2].getEigenValueForEditing() << 1, 0, 0, 0;

	std::vector<Vector<>> expectedActivations;
	expectedActivations.push_back(Vector<>(4));
	expectedActivations.push_back(Vector<>(6));
	expectedActivations.push_back(Vector<>(5));
	expectedActivations[0].getEigenValueForEditing() << 1, 2, 3, 0;
	expectedActivations[1].getEigenValueForEditing() << 1, 2, 3, 4, 0, 0;
	expectedActivations[2].getEigenValueForEditing() << 1, 2, 0, 0, 0;

	std::vector<Matrix<>> expectedWeights;
	expectedWeights.push_back(Matrix<>(5, 4));
	expectedWeights.push_back(Matrix<>(4, 6));
	expectedWeights[0].getEigenValueForEditing().row(0) << 1, 2, 3, 0;
	expectedWeights[0].getEigenValueForEditing().row(1) << 4, 5, 6, 0,
	expectedWeights[0].getEigenValueForEditing().row(2) << 7, 8, 9, 0;
	expectedWeights[0].getEigenValueForEditing().row(3) << 0, 0, 0, 0;
	expectedWeights[0].getEigenValueForEditing().row(4) << 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(1) << 0, 0, 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(2) << 0, 0, 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(3) << 0, 0, 0, 0, 0, 0;


	netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	EXPECT_EQ(3, netInputs.size());
	EXPECT_EQ(3, netInputs[0].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[0], netInputs[0]);
	EXPECT_EQ(5, netInputs[1].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[1], netInputs[1]);
	EXPECT_EQ(4, netInputs[2].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[2], netInputs[2]);

	activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	EXPECT_EQ(3, activations.size());
	EXPECT_EQ(4, activations[0].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[0], activations[0]);
	EXPECT_EQ(6, activations[1].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[1], activations[1]);
	EXPECT_EQ(5, activations[2].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[2], activations[2]);

	weights = network->getAllWeights();
	EXPECT_EQ(2, weights.size());
	EXPECT_EQ(5, weights[0].getEigenValue().rows());
	EXPECT_EQ(4, weights[0].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[0], weights[0]);
	EXPECT_EQ(4, weights[1].getEigenValue().rows());
	EXPECT_EQ(6, weights[1].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[1], weights[1]);
}


TEST_F(FeedForwardNetworkTopologyTest, addNeuronWithShortcuts)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	options.enableShortcuts = true;
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	netInputs[0].getEigenValueForEditing() << 1, 2;
	netInputs[1].getEigenValueForEditing() << 1, 2, 3;
	netInputs[2].getEigenValueForEditing() << 1;

	auto& activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	activations[2].getEigenValueForEditing().col(0) << 1, 2, 3, 2, 3, 4, 2;

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 1, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 5, 6,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4, 5, 6;

	network->addNeuron(0);
	network->addNeuron(1);
	network->addNeuron(1);
	network->addNeuron(2);
	network->addNeuron(2);
	network->addNeuron(2);

	std::vector<Vector<>> expectedNetInputs;
	expectedNetInputs.push_back(Vector<>(3));
	expectedNetInputs.push_back(Vector<>(5));
	expectedNetInputs.push_back(Vector<>(4));
	expectedNetInputs[0].getEigenValueForEditing() << 1, 2, 0;
	expectedNetInputs[1].getEigenValueForEditing() << 1, 2, 3, 0, 0;
	expectedNetInputs[2].getEigenValueForEditing() << 1, 0, 0, 0;

	std::vector<Vector<>> expectedActivations;
	expectedActivations.push_back(Vector<>(4));
	expectedActivations.push_back(Vector<>(9));
	expectedActivations.push_back(Vector<>(13));
	expectedActivations[0].getEigenValueForEditing() << 1, 2, 3, 0;
	expectedActivations[1].getEigenValueForEditing() << 1, 2, 3, 0, 2, 3, 4, 0, 0;
	expectedActivations[2].getEigenValueForEditing() << 1, 2, 3, 0, 2, 3, 4, 0, 0, 2, 0, 0, 0;

	std::vector<Matrix<>> expectedWeights;
	expectedWeights.push_back(Matrix<>(5, 4));
	expectedWeights.push_back(Matrix<>(4, 9));
	expectedWeights[0].getEigenValueForEditing().row(0) << 1, 2, 3, 0;
	expectedWeights[0].getEigenValueForEditing().row(1) << 4, 5, 6, 0,
	expectedWeights[0].getEigenValueForEditing().row(2) << 7, 8, 9, 0;
	expectedWeights[0].getEigenValueForEditing().row(3) << 0, 0, 0, 0;
	expectedWeights[0].getEigenValueForEditing().row(4) << 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 0, 4, 5, 6, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(1) << 0, 0, 0, 0, 0, 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(2) << 0, 0, 0, 0, 0, 0, 0, 0, 0;
	expectedWeights[1].getEigenValueForEditing().row(3) << 0, 0, 0, 0, 0, 0, 0, 0, 0;


	netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	EXPECT_EQ(3, netInputs.size());
	EXPECT_EQ(3, netInputs[0].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[0], netInputs[0]);
	EXPECT_EQ(5, netInputs[1].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[1], netInputs[1]);
	EXPECT_EQ(4, netInputs[2].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[2], netInputs[2]);

	activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	EXPECT_EQ(3, activations.size());
	EXPECT_EQ(4, activations[0].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[0], activations[0]);
	EXPECT_EQ(9, activations[1].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[1], activations[1]);
	EXPECT_EQ(13, activations[2].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[2], activations[2]);

	weights = network->getAllWeights();
	EXPECT_EQ(2, weights.size());
	EXPECT_EQ(5, weights[0].getEigenValue().rows());
	EXPECT_EQ(4, weights[0].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[0], weights[0]);
	EXPECT_EQ(4, weights[1].getEigenValue().rows());
	EXPECT_EQ(9, weights[1].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[1], weights[1]);
}


TEST_F(FeedForwardNetworkTopologyTest, removeNeuron)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	netInputs[0].getEigenValueForEditing() << 1, 2;
	netInputs[1].getEigenValueForEditing() << 1, 2, 3;
	netInputs[2].getEigenValueForEditing() << 1;

	auto& activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	activations[0].getEigenValueForEditing().col(0) << 1, 2, 3;
	activations[1].getEigenValueForEditing().col(0) << 1, 2, 3, 4;
	activations[2].getEigenValueForEditing().col(0) << 1, 2;

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 1, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 5, 6,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4;

	network->removeNeuron(0, 0);
	network->removeNeuron(1, 1);
	network->removeNeuron(2, 0);

	std::vector<Vector<>> expectedNetInputs;
	expectedNetInputs.push_back(Vector<>(1));
	expectedNetInputs.push_back(Vector<>(2));
	expectedNetInputs.push_back(Vector<>(0));
	expectedNetInputs[0].getEigenValueForEditing() << 2;
	expectedNetInputs[1].getEigenValueForEditing() << 1, 3;

	std::vector<Vector<>> expectedActivations;
	expectedActivations.push_back(Vector<>(2));
	expectedActivations.push_back(Vector<>(3));
	expectedActivations.push_back(Vector<>(1));
	expectedActivations[0].getEigenValueForEditing() << 2, 3;
	expectedActivations[1].getEigenValueForEditing() << 1, 3, 4;
	expectedActivations[2].getEigenValueForEditing() << 2;

	std::vector<Matrix<>> expectedWeights;
	expectedWeights.push_back(Matrix<>(2, 2));
	expectedWeights.push_back(Matrix<>(0, 3));
	expectedWeights[0].getEigenValueForEditing().row(0) << 2, 3;
	expectedWeights[0].getEigenValueForEditing().row(1) << 8, 9;

	netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	EXPECT_EQ(3, netInputs.size());
	EXPECT_EQ(1, netInputs[0].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[0], netInputs[0]);
	EXPECT_EQ(2, netInputs[1].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[1], netInputs[1]);
	EXPECT_EQ(0, netInputs[2].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[2], netInputs[2]);

	activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	EXPECT_EQ(3, activations.size());
	EXPECT_EQ(2, activations[0].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[0], activations[0]);
	EXPECT_EQ(3, activations[1].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[1], activations[1]);
	EXPECT_EQ(1, activations[2].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[2], activations[2]);

	weights = network->getAllWeights();
	EXPECT_EQ(2, weights.size());
	EXPECT_EQ(2, weights[0].getEigenValue().rows());
	EXPECT_EQ(2, weights[0].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[0], weights[0]);
	EXPECT_EQ(0, weights[1].getEigenValue().rows());
	EXPECT_EQ(3, weights[1].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[1], weights[1]);
}



TEST_F(FeedForwardNetworkTopologyTest, removeNeuronWithShortcuts)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	options.enableShortcuts = true;
	network = new FeedForwardNetworkTopology(options);

	auto& netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	netInputs[0].getEigenValueForEditing() << 1, 2;
	netInputs[1].getEigenValueForEditing() << 1, 2, 3;
	netInputs[2].getEigenValueForEditing() << 1;

	auto& activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	activations[2].getEigenValueForEditing().col(0) << 1, 2, 3, 2, 3, 4, 2;

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 1, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 5, 6,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4, 5, 6;

	network->removeNeuron(0, 0);
	network->removeNeuron(1, 1);

	std::vector<Vector<>> expectedNetInputs;
	expectedNetInputs.push_back(Vector<>(1));
	expectedNetInputs.push_back(Vector<>(2));
	expectedNetInputs.push_back(Vector<>(1));
	expectedNetInputs[0].getEigenValueForEditing() << 2;
	expectedNetInputs[1].getEigenValueForEditing() << 1, 3;
	expectedNetInputs[2].getEigenValueForEditing() << 1;

	std::vector<Vector<>> expectedActivations;
	expectedActivations.push_back(Vector<>(2));
	expectedActivations.push_back(Vector<>(4));
	expectedActivations.push_back(Vector<>(5));
	expectedActivations[0].getEigenValueForEditing() << 2, 3;
	expectedActivations[1].getEigenValueForEditing() << 2, 3, 2, 4;
	expectedActivations[2].getEigenValueForEditing() << 2, 3, 2, 4, 2;

	std::vector<Matrix<>> expectedWeights;
	expectedWeights.push_back(Matrix<>(2, 2));
	expectedWeights.push_back(Matrix<>(1, 4));
	expectedWeights[0].getEigenValueForEditing().row(0) << 2, 3;
	expectedWeights[0].getEigenValueForEditing().row(1) << 8, 9;
	expectedWeights[1].getEigenValueForEditing().row(0) << 2, 3, 4, 6;

	netInputs = const_cast<std::vector<Vector<>>&>(network->getAllNetInputs());
	EXPECT_EQ(3, netInputs.size());
	EXPECT_EQ(1, netInputs[0].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[0], netInputs[0]);
	EXPECT_EQ(2, netInputs[1].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[1], netInputs[1]);
	EXPECT_EQ(1, netInputs[2].getEigenValue().rows());
	EXPECT_EQ(expectedNetInputs[2], netInputs[2]);

	activations = const_cast<std::vector<Vector<>>&>(network->getAllActivations());
	EXPECT_EQ(3, activations.size());
	EXPECT_EQ(2, activations[0].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[0], activations[0]);
	EXPECT_EQ(4, activations[1].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[1], activations[1]);
	EXPECT_EQ(5, activations[2].getEigenValue().rows());
	EXPECT_EQ(expectedActivations[2], activations[2]);

	weights = network->getAllWeights();
	EXPECT_EQ(2, weights.size());
	EXPECT_EQ(2, weights[0].getEigenValue().rows());
	EXPECT_EQ(2, weights[0].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[0], weights[0]);
	EXPECT_EQ(1, weights[1].getEigenValue().rows());
	EXPECT_EQ(4, weights[1].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[1], weights[1]);
}



TEST_F(FeedForwardNetworkTopologyTest, removeAfferentWeight)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	network = new FeedForwardNetworkTopology(options);

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 1, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 5, 6,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 4;

	network->removeAfferentWeight(0, 0, 0);
	network->removeAfferentWeight(0, 1, 1);
	network->removeAfferentWeight(0, 2, 1);
	network->removeAfferentWeight(1, 3, 0);

	std::vector<Matrix<>> expectedWeights;
	expectedWeights.push_back(Matrix<>(3, 3));
	expectedWeights.push_back(Matrix<>(1, 4));
	expectedWeights[0].getEigenValueForEditing().row(0) << 0, 2, 3;
	expectedWeights[0].getEigenValueForEditing().row(1) << 4, 0, 0,
	expectedWeights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	expectedWeights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 0;

	weights = network->getAllWeights();
	EXPECT_EQ(2, weights.size());
	EXPECT_EQ(3, weights[0].getEigenValue().rows());
	EXPECT_EQ(3, weights[0].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[0], weights[0]);
	EXPECT_EQ(1, weights[1].getEigenValue().rows());
	EXPECT_EQ(4, weights[1].getEigenValue().cols());
	EXPECT_EQ(expectedWeights[1], weights[1]);
}


TEST_F(FeedForwardNetworkTopologyTest, existsAfferentWeight)
{
	FeedForwardNetworkTopologyOptions options = getDefaultOptions();
	network = new FeedForwardNetworkTopology(options);

	auto& weights = network->getAllWeights();
	weights[0].getEigenValueForEditing().row(0) << 0, 2, 3;
	weights[0].getEigenValueForEditing().row(1) << 4, 0, 0,
	weights[0].getEigenValueForEditing().row(2) << 7, 8, 9;
	weights[1].getEigenValueForEditing().row(0) << 1, 2, 3, 0;

	EXPECT_EQ(true, network->existsAfferentWeight(1, 2, 0));
	EXPECT_EQ(true, network->existsAfferentWeight(0, 2, 2));
	EXPECT_EQ(false, network->existsAfferentWeight(0, 0, 0));
	EXPECT_EQ(false, network->existsAfferentWeight(1, 3, 0));
}