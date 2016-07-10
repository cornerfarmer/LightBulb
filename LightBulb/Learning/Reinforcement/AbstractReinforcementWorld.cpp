// Includes
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"
#include <ActivationOrder/TopologicalOrder.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>

//Library include

void AbstractReinforcementWorld::doNNCalculation()
{
	neuralNetwork->getNetworkTopology()->resetActivation();
	// Get the input
	getNNInput(lastInput);

	TopologicalOrder topologicalOrder;
	// Calculate the output from the the input
	neuralNetwork->calculate(lastInput, lastOutput, topologicalOrder, false);

	for (int i = 0; i < lastOutput.size(); i++)
	{
		lastBooleanOutput[i] = ((double)rand() / RAND_MAX < lastOutput[i]);
	}

	// Interpret the output
	interpretNNOutput(lastBooleanOutput);
}

AbstractReinforcementWorld::AbstractReinforcementWorld(LayeredNetworkOptions& options)
{
	buildNeuralNetwork(options);
}

void AbstractReinforcementWorld::initializeForLearning()
{
	// Randomize all weights
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5, 0.5);
}

NeuralNetwork* AbstractReinforcementWorld::getNeuralNetwork()
{
	return neuralNetwork.get();
}

void AbstractReinforcementWorld::setLearningState(LearningState* learningState_)
{
	learningState = learningState_;
}

void AbstractReinforcementWorld::buildNeuralNetwork(LayeredNetworkOptions& options)
{
	// Create a new network topology from the adjusted options.
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);

	// Create a neural network from the network topolgy
	neuralNetwork.reset(new NeuralNetwork(layeredNetwork));

	// Initialize the mutation strength vector
	buildOutputBuffer();
}


void AbstractReinforcementWorld::buildOutputBuffer()
{
	lastOutput.resize(neuralNetwork->getNetworkTopology()->getOutputSize());
	lastBooleanOutput.resize(lastOutput.size());
}

std::vector<std::string> AbstractReinforcementWorld::getDataSetLabels()
{
	std::vector<std::string> labels;
	return labels;
}

std::vector<bool> AbstractReinforcementWorld::getLastBooleanOutput()
{
	return lastBooleanOutput;
}
