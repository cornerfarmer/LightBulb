// Includes
#include "NetworkTopology\HopfieldNetwork.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Function\IdentityFunction.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\BinaryFunction.hpp"
#include "Function\FermiFunction.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "Neuron\Edge.hpp"
#include "Teaching\Teacher.hpp"
//  Library includes
#include <algorithm>  

HopfieldNetwork::HopfieldNetwork(unsigned int neuronCount, bool binaryActivationFunction)
{
	// Check if all given options are correct
	if (neuronCount == 0)
		throw std::invalid_argument("The given neuronCount has to be greater than 0");

	// Create a new options object
	options.reset(new FreeNetworkOptions());
	// Set all options
	options->inputNeuronsIndices.resize(neuronCount);
	options->outputNeuronsIndices.resize(neuronCount);
	for (int i = 0; i < neuronCount; i++)
	{
		options->inputNeuronsIndices[i] = i;
		options->outputNeuronsIndices[i] = i;
	}
	options->useBiasNeuron = false;
	options->selfReferencingEdges = false;
	options->neuronCount = neuronCount;
	// Define thresholds and functions
	options->neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), (binaryActivationFunction ? static_cast<AbstractActivationFunction*>(new BinaryFunction(-1)) : static_cast<AbstractActivationFunction*>(new FermiFunction(0.1))), new IdentityFunction());

	// Build the network
	buildNetwork();

}
