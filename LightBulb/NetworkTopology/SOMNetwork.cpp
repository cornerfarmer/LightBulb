// Includes
#include "NetworkTopology/SOMNetwork.hpp"
#include "NeuronFactory/SameFunctionsNeuronFactory.hpp"
#include "Function/EuclideanDistance.hpp"
#include "Function/IdentityFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "Function/MinimumNetInputActivationFunction.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/BinaryFunction.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "Neuron/Edge.hpp"
#include "Teaching/Teacher.hpp"
#include "NetworkTopology/AbstractSOMStructure.hpp"
//  Library includes
#include <algorithm>  


SOMNetwork::SOMNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, AbstractSOMStructure* somStructure)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (codebookVectorCount == 0)
		throw std::invalid_argument("The given codebookVectorCount has to be greater than 0");

	structure = somStructure;

	// Create a new options object
	options.reset(new FeedForwardNetworkTopologyOptions());
	// Set all options
	// Define thresholds and functions
	options->neuronFactory = new SameFunctionsNeuronFactory(new NeuronCompareThreshold(NULL), new EuclideanDistance(), new MinimumNetInputActivationFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(2);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = codebookVectorCount;

	// Build the network
	buildNetwork();

	// Go through all neurons in the output layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Set the neurons vector of the threshold to the neuron vector of the output layer
		static_cast<NeuronCompareThreshold*>((*neuron)->getThreshold())->setNeurons(&neurons.front());
	}

	structure->initialize(*this);
}

int SOMNetwork::getCodebookVectorCount()
{
	return neurons[0].size();
}

AbstractSOMStructure* SOMNetwork::getStructure()
{
	return structure;
}