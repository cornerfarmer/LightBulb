#include "RBFNetwork.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"
#include "RBFThreshold.hpp"
#include "EuclideanDistance.hpp"
#include "GaussianRBFFunction.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "StandardThreshold.hpp"
#include "Edge.hpp"
#include "StandardNeuron.hpp"

RBFNetwork::RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer)
{
	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->enableShortcuts = false;
	options->useBiasNeuron = false;
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new RBFThreshold(std::vector<float>(neuronCountFirstLayer, 0), 0.5), new EuclideanDistance(), new GaussianRBFFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = neuronCountFirstLayer;
	options->neuronsPerLayerCount[1] = neuronCountSecondLayer;
	options->neuronsPerLayerCount[2] = neuronCountThirdLayer;	

	// Build the network
	buildNetwork();
}

void RBFNetwork::randomizeWeights(float randStart, float randEnd)
{	
	// Go through all neurons in the first hidden layer
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Go through all effernetEdges of this neuron
		std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			do{
				// Set the weight to a new random value
				(*edge)->setWeight((float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
			} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
		}
	}	
}

void RBFNetwork::randomizeCenters(float randStart, float randEnd)
{
	// Go through all neurons in the first hidden layer
	for (int neuronIndex = 0; neuronIndex != neurons.front().size(); neuronIndex++)
	{
		// Create a new center vector and fill it with random values
		std::vector<float> newCenter(inputNeurons.size());
		for (std::vector<float>::iterator centerCoordinate = newCenter.begin(); centerCoordinate != newCenter.end(); centerCoordinate++)
			*centerCoordinate = (float)rand() / RAND_MAX * (randEnd - randStart) + randStart;
		// Set the new center vector to the neuron
		setCenterOfRBFNeuron(neuronIndex, newCenter);
	}	
}
	
void RBFNetwork::randomizeWidths(float randStart, float randEnd)
{
	// Go through all neurons in the second layer
	for (int neuronIndex = 0; neuronIndex != neurons.front().size(); neuronIndex++)
	{
		// Set a new random width to the neuron
		setWidthOfRBFNeuron(neuronIndex, (float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
	}
}

void RBFNetwork::setCenterOfRBFNeuron(int neuronIndex, std::vector<float> &newCenterPosition)
{
	// Set the new center position to the neuron with neuronIndex
	dynamic_cast<RBFThreshold*>(neurons.front()[neuronIndex]->getThreshold())->setCenterVector(newCenterPosition);
}

void RBFNetwork::setWidthOfRBFNeuron(int neuronIndex, float newWidth)
{
	// Set the new width to the neuron with neuronIndex
	dynamic_cast<RBFThreshold*>(neurons.front()[neuronIndex]->getThreshold())->setWidth(newWidth);
}