// Includes
#include "NetworkTopology\LVQNetwork.hpp"
#include "NeuronFactory\DifferentFunctionsNeuronFactory.hpp"
#include "Function\EuclideanDistance.hpp"
#include "Function\IdentityFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "Function\MinimumNetInputActivationFunction.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\BinaryFunction.hpp"
#include "Neuron\StandardThreshold.hpp"

LVQNetwork::LVQNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int classCount)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (codebookVectorCount == 0)
		throw std::invalid_argument("The given codebookVectorCount has to be greater than 0");
	if (classCount == 0)
		throw std::invalid_argument("The given classCount has to be greater than 0");

	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->useBiasNeuron = false;
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new NeuronCompareThreshold(NULL), new EuclideanDistance(), new MinimumNetInputActivationFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new BinaryFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = codebookVectorCount;
	options->neuronsPerLayerCount[2] = classCount;

	// Build the network
	buildNetwork();

	// Go through all neurons in the output layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Set the neurons vector of the threshold to the neuron vector of the output layer
		static_cast<NeuronCompareThreshold*>((*neuron)->getThreshold())->setNeurons(&neurons.front());
	}
}

int LVQNetwork::getClassCount()
{
	return neurons[0].size();
}

int LVQNetwork::getCodebookVectorCount()
{
	return neurons[1].size();
}