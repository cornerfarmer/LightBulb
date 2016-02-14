// Includes
#include "NetworkTopology/RBFNetwork.hpp"
#include "NeuronFactory/DifferentFunctionsNeuronFactory.hpp"
#include "Neuron/RBFThreshold.hpp"
#include "Function/EuclideanDistance.hpp"
#include "Function/GaussianRBFFunction.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "Neuron/Edge.hpp"
#include "Neuron/StandardNeuron.hpp"

RBFNetwork::RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer)
{
	// Check if all given options are correct
	if (neuronCountFirstLayer == 0)
		throw std::invalid_argument("The given neuronCountFirstLayer has to be greater than 0");
	if (neuronCountSecondLayer == 0)
		throw std::invalid_argument("The given neuronCountSecondLayer has to be greater than 0");
	if (neuronCountThirdLayer == 0)
		throw std::invalid_argument("The given neuronCountThirdLayer has to be greater than 0");

	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->enableShortcuts = false;
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new RBFThreshold(0.5), new EuclideanDistance(), new GaussianRBFFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = neuronCountFirstLayer;
	options->neuronsPerLayerCount[1] = neuronCountSecondLayer;
	options->neuronsPerLayerCount[2] = neuronCountThirdLayer;	

	// Build the network
	buildNetwork();
}

void RBFNetwork::randomizeWeights(double randStart, double randEnd)
{	
	// Go through all neurons in the first hidden layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Go through all effernetEdges of this neuron
		std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
		for (auto edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			do{
				// Set the weight to a new random value
				(*edge)->randomizeWeight(randStart, randEnd);
			} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
		}
	}	
}

void RBFNetwork::randomizeCenters(double randStart, double randEnd)
{
	// Go through all neurons in the first hidden layer
	for (int neuronIndex = 0; neuronIndex != neurons.front().size(); neuronIndex++)
	{
		// Create a new center vector and fill it with random values
		std::vector<double> newCenter(inputNeurons.size());
		for (auto centerCoordinate = newCenter.begin(); centerCoordinate != newCenter.end(); centerCoordinate++)
			*centerCoordinate = (double)rand() / RAND_MAX * (randEnd - randStart) + randStart;
		// Set the new center vector to the neuron
		setCenterOfRBFNeuron(neuronIndex, newCenter);
	}	
}
	
void RBFNetwork::randomizeWidths(double randStart, double randEnd)
{
	// Go through all neurons in the second layer
	for (int neuronIndex = 0; neuronIndex != neurons.front().size(); neuronIndex++)
	{
		// Set a new random width to the neuron
		setWidthOfRBFNeuron(neuronIndex, (double)rand() / RAND_MAX * (randEnd - randStart) + randStart);
	}
}

void RBFNetwork::setCenterOfRBFNeuron(int neuronIndex, std::vector<double> &newCenterPosition)
{
	// Set the new center position to the neuron with neuronIndex
	auto centerCoordinate = newCenterPosition.begin();
	for(auto edge = neurons.front()[neuronIndex]->getAfferentEdges()->begin(); edge != neurons.front()[neuronIndex]->getAfferentEdges()->end(); edge++, centerCoordinate++)
	{
		(*edge)->setWeight(*centerCoordinate);
	}	
}

void RBFNetwork::setWidthOfRBFNeuron(int neuronIndex, double newWidth)
{
	// Set the new width to the neuron with neuronIndex
	dynamic_cast<RBFThreshold*>(neurons.front()[neuronIndex]->getThreshold())->setWidth(newWidth);
}