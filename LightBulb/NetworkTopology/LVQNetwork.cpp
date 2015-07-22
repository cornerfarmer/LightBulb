// Includes
#include "NetworkTopology\LVQNetwork.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Function\EuclideanDistance.hpp"
#include "Function\IdentityFunction.hpp"
#include "Neuron\NeuronCompareThreshold.hpp"
#include "Function\MinimumNetInputActivationFunction.hpp"
#include "Neuron\StandardNeuron.hpp"


LVQNetwork::LVQNetwork(unsigned int inputNeuronCount, unsigned int outputNeuronCount)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (outputNeuronCount == 0)
		throw std::invalid_argument("The given outputNeuronCount has to be greater than 0");

	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->useBiasNeuron = false;
	// Define thresholds and functions
	options->neuronFactory = new SameFunctionsNeuronFactory(new NeuronCompareThreshold(NULL), new EuclideanDistance(), new MinimumNetInputActivationFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(2);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = outputNeuronCount;

	// Build the network
	buildNetwork();

	// Go through all neurons in the output layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Set the neurons vector of the threshold to the neuron vector of the output layer
		static_cast<NeuronCompareThreshold*>((*neuron)->getThreshold())->setNeurons(&neurons.front());
	}
}
