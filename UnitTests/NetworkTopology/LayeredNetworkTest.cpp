#include "gtest/gtest.h"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Function/FermiFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "Function/WeightedSumFunction.hpp"

class LayeredNetworkTest : public testing::Test {
public:
	LayeredNetwork* network;
	void SetUp() {
		LayeredNetworkOptions options;
		options.neuronsPerLayerCount.push_back(2);
		options.neuronsPerLayerCount.push_back(3);
		options.neuronsPerLayerCount.push_back(1);
		options.activationFunction = new FermiFunction(1);
		options.inputFunction = new WeightedSumFunction();
		options.outputFunction = new IdentityFunction();
		options.threshold = new StandardThreshold(0);
		options.useBiasNeuron = true;

		network = new LayeredNetwork(options);
	}

	virtual ~LayeredNetworkTest()
	{
		delete network;
	}
};

TEST_F(LayeredNetworkTest, createSimpleNetwork)
{
	auto netInputs = network->getNetInputs();
	EXPECT_EQ(netInputs->size(), 3);
	EXPECT_EQ((*netInputs)[0].rows(), 3);
	EXPECT_EQ((*netInputs)[1].rows(), 4);
	EXPECT_EQ((*netInputs)[2].rows(), 2);

	auto activations = network->getActivations();
	EXPECT_EQ(activations->size(), 3);
	EXPECT_EQ((*activations)[0].rows(), 3);
	EXPECT_EQ((*activations)[1].rows(), 4);
	EXPECT_EQ((*activations)[2].rows(), 2);

	auto weights = network->getWeights();
	EXPECT_EQ(weights->size(), 2);
	EXPECT_EQ((*weights)[0].rows(), 3);
	EXPECT_EQ((*weights)[0].cols(), 3);
	EXPECT_EQ((*weights)[1].rows(), 1);
	EXPECT_EQ((*weights)[1].cols(), 4);
}
