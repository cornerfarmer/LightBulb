#include "gtest/gtest.h"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include "Function/InputFunction/WeightedSumFunction.hpp"
#include "NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "NeuronDescription/NeuronDescription.hpp"
#include <NetworkTopology/RBFNetwork.hpp>

class RBFNetworkTest : public testing::Test {
public:
	RBFNetwork* network;
	void SetUp() {
		network = new RBFNetwork(2, 3, 1);
	}

	virtual ~RBFNetworkTest()
	{
		delete network;
	}
};

TEST_F(RBFNetworkTest, createSimpleNetwork)
{
	auto netInputs = network->getAllNetInputs();
	EXPECT_EQ(3, netInputs->size());
	EXPECT_EQ(2, (*netInputs)[0].rows());
	EXPECT_EQ(3, (*netInputs)[1].rows());
	EXPECT_EQ(1, (*netInputs)[2].rows());

	auto activations = network->getAllActivations();
	EXPECT_EQ(3, activations->size());
	EXPECT_EQ(2, (*activations)[0]->rows());
	EXPECT_EQ(3, (*activations)[1]->rows());
	EXPECT_EQ(1, (*activations)[2]->rows());

	auto weights = network->getAllWeights();
	EXPECT_EQ(2, weights->size());
	EXPECT_EQ(3, (*weights)[0].rows());
	EXPECT_EQ(2, (*weights)[0].cols());
	EXPECT_EQ(1, (*weights)[1].rows());
	EXPECT_EQ(3, (*weights)[1].cols());
}

TEST_F(RBFNetworkTest, setWidthOfRBFNeuron)
{
	network->setWidthOfRBFNeuron(0, 1);
	network->setWidthOfRBFNeuron(1, 2);
	network->setWidthOfRBFNeuron(2, 3);

	EXPECT_EQ(1, network->getWidthOfRBFNeuron(0));
	EXPECT_EQ(2, network->getWidthOfRBFNeuron(1));
	EXPECT_EQ(3, network->getWidthOfRBFNeuron(2));
}

TEST_F(RBFNetworkTest, setCenterOfRBFNeuron)
{
	std::vector<double> center(2);
	center[0] = 1;
	center[1] = 2;
	network->setCenterOfRBFNeuron(0, center);
	center[0] = 3;
	center[1] = 4;
	network->setCenterOfRBFNeuron(1, center);
	center[0] = 5;
	center[1] = 6;
	network->setCenterOfRBFNeuron(2, center);

	Eigen::MatrixXd centers = network->getAfferentWeightsPerLayer(1);
	Eigen::MatrixXd expectedCenters(3, 2);
	expectedCenters << 1, 2, 3, 4, 5, 6;
					
	EXPECT_TRUE(expectedCenters.isApprox(centers));
}

