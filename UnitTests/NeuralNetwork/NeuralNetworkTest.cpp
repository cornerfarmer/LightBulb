#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <NeuralNetwork/NeuralNetwork.hpp>
#include "Mocks/MockAbstractNetworkTopology.hpp"
#include "Mocks/MockAbstractActivationOrder.hpp"

using testing::Expectation;

class NeuralNetworkTest : public testing::Test {
public:
	NeuralNetwork* neuralNetwork;
	MockAbstractNetworkTopology* networkTopology;
	MockAbstractActivationOrder* activationOrder;
	void SetUp() {
		networkTopology = new MockAbstractNetworkTopology();
		activationOrder = new MockAbstractActivationOrder();
		neuralNetwork = new NeuralNetwork(networkTopology);
	}

	virtual ~NeuralNetworkTest()
	{
		delete neuralNetwork;
	}
};

TEST_F(NeuralNetworkTest, calculateSimple)
{
	std::vector<double> input(3);
	std::vector<double> output(2);

	Expectation resetActivation = EXPECT_CALL(*networkTopology, resetActivation()).Times(1);
	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input)).Times(1).After(resetActivation);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output)).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder);
}


TEST_F(NeuralNetworkTest, calculateSimpleWithoutReset)
{
	std::vector<double> input(3);
	std::vector<double> output(2);

	EXPECT_CALL(*networkTopology, resetActivation()).Times(0);
	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input)).Times(1);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output)).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder, false);
}

TEST_F(NeuralNetworkTest, calculate)
{
	std::vector<std::vector<double>> input(3, std::vector<double>(3));
	std::vector<std::vector<double>> output(3, std::vector<double>(2));

	Expectation resetActivation = EXPECT_CALL(*networkTopology, resetActivation()).Times(1);
	Expectation setInput0 = EXPECT_CALL(*networkTopology, setInput(input[0])).Times(1).After(resetActivation);
	Expectation executeActivation0 = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput0);
	Expectation getOutput0 = EXPECT_CALL(*networkTopology, getOutput(output[0])).Times(1).After(executeActivation0);

	Expectation setInput1 = EXPECT_CALL(*networkTopology, setInput(input[1])).Times(1).After(getOutput0);
	Expectation executeActivation1 = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput1);
	Expectation getOutput1 = EXPECT_CALL(*networkTopology, getOutput(output[1])).Times(1).After(executeActivation1);

	Expectation setInput2 = EXPECT_CALL(*networkTopology, setInput(input[2])).Times(1).After(getOutput1);
	Expectation executeActivation2 = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput2);
	Expectation getOutput2 = EXPECT_CALL(*networkTopology, getOutput(output[2])).Times(1).After(executeActivation2);
	
	neuralNetwork->calculate(input, output, *activationOrder);
}


TEST_F(NeuralNetworkTest, calculateWithStartTime)
{
	std::vector<std::vector<double>> input(2, std::vector<double>(3));
	std::vector<std::vector<double>> output(2, std::vector<double>(2));

	EXPECT_CALL(*networkTopology, resetActivation()).Times(0);
	EXPECT_CALL(*networkTopology, setInput(input[0])).Times(0);
	EXPECT_CALL(*networkTopology, getOutput(output[0])).Times(0);

	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input[1])).Times(1);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output[1])).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder, 1);
}

TEST_F(NeuralNetworkTest, calculateWithTimeStepCount)
{
	std::vector<std::vector<double>> input(3, std::vector<double>(3));
	std::vector<std::vector<double>> output(3, std::vector<double>(2));

	EXPECT_CALL(*networkTopology, resetActivation()).Times(0);
	EXPECT_CALL(*networkTopology, setInput(input[0])).Times(0);
	EXPECT_CALL(*networkTopology, getOutput(output[0])).Times(0);
	EXPECT_CALL(*networkTopology, setInput(input[2])).Times(0);
	EXPECT_CALL(*networkTopology, getOutput(output[2])).Times(0);

	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input[1])).Times(1);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output[1])).Times(1).After(executeActivation);

	neuralNetwork->calculate(input, output, *activationOrder, 1, 1);
}

TEST_F(NeuralNetworkTest, calculateWithOutputValues)
{
	std::vector<std::vector<double>> input(1, std::vector<double>(3));
	std::vector<std::vector<double>> output(1, std::vector<double>(2));
	std::vector<std::map<AbstractNeuron*, double>> outputValuesInTime(1);
	std::vector<std::map<AbstractNeuron*, double>> netInputValuesInTime(1);

	Expectation resetActivation = EXPECT_CALL(*networkTopology, resetActivation()).Times(1);
	Expectation setInput = EXPECT_CALL(*networkTopology, setInput(input[0])).Times(1).After(resetActivation);
	Expectation executeActivation = EXPECT_CALL(*activationOrder, executeActivation(testing::Ref(*networkTopology))).Times(1).After(setInput);
	Expectation getOutput = EXPECT_CALL(*networkTopology, getOutput(output[0])).Times(1).After(executeActivation);

	Expectation getAllNeuronOutputs = EXPECT_CALL(*networkTopology, getAllNeuronOutputs(outputValuesInTime[0])).Times(1).After(getOutput);
	Expectation getAllNetInputs = EXPECT_CALL(*networkTopology, getAllNeuronNetInputs(netInputValuesInTime[0])).Times(1).After(getAllNeuronOutputs);

	neuralNetwork->calculate(input, output, *activationOrder, 0, -1, &outputValuesInTime, &netInputValuesInTime);
}
