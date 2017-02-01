#include "UnitTestsPrec.hpp"
#include <LightBulb/NeuralNetwork/NeuralNetwork.hpp>
#include "Mocks/MockNetworkTopology.hpp"
#include "Mocks/MockActivationOrder.hpp"

using testing::Expectation;
using namespace LightBulb;

class NeuralNetworkTest : public testing::Test {
public:
	NeuralNetwork* neuralNetwork;
	MockNetworkTopology* networkTopology;
	MockActivationOrder* activationOrder;
	void SetUp() {
		networkTopology = new MockNetworkTopology();
		activationOrder = new MockActivationOrder();
		neuralNetwork = new NeuralNetwork(networkTopology);
	}

	virtual ~NeuralNetworkTest()
	{
		delete neuralNetwork;
		delete activationOrder;
	}
};

TEST_F(NeuralNetworkTest, calculateSimple)
{
	std::vector<double> input(3);
	std::vector<double> output(2);

	Expectation resetActivation = EXPECT_CALL(*networkTopology, resetActivation()).Times(1);
	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input)).Times(1).After(resetActivation);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology), nullptr)).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output)).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder);
}


TEST_F(NeuralNetworkTest, calculateSimpleWithoutReset)
{
	std::vector<double> input(3);
	std::vector<double> output(2);

	EXPECT_CALL(*networkTopology, resetActivation()).Times(0);
	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input)).Times(1);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology), nullptr)).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output)).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder, false);
}
