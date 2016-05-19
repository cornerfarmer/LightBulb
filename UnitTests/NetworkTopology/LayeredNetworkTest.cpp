#include "gtest/gtest.h"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Function/FermiFunction.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "NeuronFactory/SameNeuronDescriptionFactory.hpp"
#include "Neuron/NeuronDescription.hpp"

class LayeredNetworkTest : public testing::Test {
public:
	LayeredNetwork* network;
	void SetUp() {
		
	}

	LayeredNetworkOptions getDefaultOptions()
	{
		LayeredNetworkOptions options;
		options.neuronsPerLayerCount.push_back(2);
		options.neuronsPerLayerCount.push_back(3);
		options.neuronsPerLayerCount.push_back(1);
		options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
		return options;
	}

	virtual ~LayeredNetworkTest()
	{
		delete network;
	}
};

TEST_F(LayeredNetworkTest, createSimpleNetwork)
{
	LayeredNetworkOptions options = getDefaultOptions();
	network = new LayeredNetwork(options);

	auto netInputs = network->getNetInputs();
	EXPECT_EQ(netInputs->size(), 3);
	EXPECT_EQ((*netInputs)[0].rows(), 2);
	EXPECT_EQ((*netInputs)[1].rows(), 3);
	EXPECT_EQ((*netInputs)[2].rows(), 1);

	auto activations = network->getActivations();
	EXPECT_EQ(activations->size(), 3);
	EXPECT_EQ((*activations)[0]->rows(), 3);
	EXPECT_EQ((*activations)[1]->rows(), 4);
	EXPECT_EQ((*activations)[2]->rows(), 2);

	auto weights = network->getWeights();
	EXPECT_EQ(weights->size(), 2);
	EXPECT_EQ((*weights)[0].rows(), 3);
	EXPECT_EQ((*weights)[0].cols(), 3);
	EXPECT_EQ((*weights)[1].rows(), 1);
	EXPECT_EQ((*weights)[1].cols(), 4);
}


TEST_F(LayeredNetworkTest, createNetworkWithShortcuts)
{
	LayeredNetworkOptions options = getDefaultOptions();
	options.enableShortcuts = true;
	network = new LayeredNetwork(options);

	auto netInputs = network->getNetInputs();
	EXPECT_EQ(netInputs->size(), 3);
	EXPECT_EQ((*netInputs)[0].rows(), 2);
	EXPECT_EQ((*netInputs)[1].rows(), 3);
	EXPECT_EQ((*netInputs)[2].rows(), 1);

	auto activations = network->getActivations();
	EXPECT_EQ(activations->size(), 3);
	EXPECT_EQ((*activations)[0]->rows(), 3);
	EXPECT_EQ((*activations)[1]->rows(), 6);
	EXPECT_EQ((*activations)[2]->rows(), 7);

	auto weights = network->getWeights();
	EXPECT_EQ(weights->size(), 2);
	EXPECT_EQ((*weights)[0].rows(), 3);
	EXPECT_EQ((*weights)[0].cols(), 3);
	EXPECT_EQ((*weights)[1].rows(), 1);
	EXPECT_EQ((*weights)[1].cols(), 6);
}


TEST_F(LayeredNetworkTest, addNeuron)
{
	LayeredNetworkOptions options = getDefaultOptions();
	network = new LayeredNetwork(options);

	auto netInputs = network->getNetInputs();
	(*netInputs)[0] << 1, 2;
	(*netInputs)[1] << 1, 2, 3;
	(*netInputs)[2] << 1;

	auto activations = network->getActivations();
	(*activations)[0]->col(0) << 1, 2, 3;
	(*activations)[1]->col(0) << 1, 2, 3, 4;
	(*activations)[2]->col(0) << 1, 2;

	auto weights = network->getWeights();
	(*weights)[0].row(0) << 1, 2, 3;
	(*weights)[0].row(1) << 4, 5, 6,
	(*weights)[0].row(2) << 7, 8, 9;
	(*weights)[1].row(0) << 1, 2, 3, 4;

	network->addNeuron(0);
	network->addNeuron(1);
	network->addNeuron(1);
	network->addNeuron(2);
	network->addNeuron(2);
	network->addNeuron(2);

	std::vector<Eigen::VectorXd> expectedNetInputs;
	expectedNetInputs.push_back(Eigen::VectorXd(3));
	expectedNetInputs.push_back(Eigen::VectorXd(5));
	expectedNetInputs.push_back(Eigen::VectorXd(4));
	expectedNetInputs[0] << 1, 2, 0;
	expectedNetInputs[1] << 1, 2, 3, 0, 0;
	expectedNetInputs[2] << 1, 0, 0, 0;

	std::vector<Eigen::VectorXd> expectedActivations;
	expectedActivations.push_back(Eigen::VectorXd(4));
	expectedActivations.push_back(Eigen::VectorXd(6));
	expectedActivations.push_back(Eigen::VectorXd(5));
	expectedActivations[0] << 1, 2, 3, 0;
	expectedActivations[1] << 1, 2, 3, 4, 0, 0;
	expectedActivations[2] << 1, 2, 0, 0, 0;

	std::vector<Eigen::MatrixXd> expectedWeights;
	expectedWeights.push_back(Eigen::MatrixXd(3,3));
	expectedWeights.push_back(Eigen::MatrixXd(1, 4));
	expectedWeights[0].row(0) << 1, 2, 3;
	expectedWeights[0].row(1) << 4, 5, 6,
	expectedWeights[0].row(2) << 7, 8, 9;
	expectedWeights[1].row(0) << 1, 2, 3, 4;

	netInputs = network->getNetInputs();
	EXPECT_EQ(3, netInputs->size());
	EXPECT_EQ(3, (*netInputs)[0].rows());
	EXPECT_EQ(expectedNetInputs[0], (*netInputs)[0]);
	EXPECT_EQ(5, (*netInputs)[1].rows());
	EXPECT_EQ(expectedNetInputs[1], (*netInputs)[1]);
	EXPECT_EQ(4, (*netInputs)[2].rows());
	EXPECT_EQ(expectedNetInputs[2], (*netInputs)[2]);

	activations = network->getActivations();
	EXPECT_EQ(3, activations->size());
	EXPECT_EQ(4, (*activations)[0]->rows());
	EXPECT_EQ(expectedActivations[0], *(*activations)[0]);
	EXPECT_EQ(6, (*activations)[1]->rows());
	EXPECT_EQ(expectedActivations[1], *(*activations)[1]);
	EXPECT_EQ(5, (*activations)[2]->rows());
	EXPECT_EQ(expectedActivations[2], *(*activations)[2]);

	weights = network->getWeights();
	EXPECT_EQ(2, weights->size());
	EXPECT_EQ(5, (*weights)[0].rows());
	EXPECT_EQ(4, (*weights)[0].cols());
	EXPECT_EQ(4, (*weights)[1].rows());
	EXPECT_EQ(6, (*weights)[1].cols());
}