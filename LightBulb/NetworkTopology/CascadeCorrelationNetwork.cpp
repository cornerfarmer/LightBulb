// Includes
#include "NetworkTopology\CascadeCorrelationNetwork.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\IdentityFunction.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "Function\FermiFunction.hpp"
#include "Function\HyperbolicTangentFunction.hpp"

CascadeCorrelationNetwork::CascadeCorrelationNetwork(unsigned int inputNeuronCount, unsigned int outputNeuronCount)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (outputNeuronCount == 0)
		throw std::invalid_argument("The given outputNeuronCount has to be greater than 0");

	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->enableShortcuts = true;
	options->useBiasNeuron = true;
	// Define thresholds and functions
	options->neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new HyperbolicTangentFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(2);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = outputNeuronCount;

	// Build the network
	buildNetwork();
}
