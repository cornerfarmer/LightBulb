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
	options->enableDirectBackCoupling = false;
	options->enableDirectBackCoupling = false;
	options->enableIndirectBackCoupling = false;
	options->enableLateralBackCoupling = false;
	options->enableShortcuts = false;
	options->useBiasNeurons = false;
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
	// Go through all neurons in the second layer
	for (std::vector<AbstractNeuron*>::iterator neuron = getNeuronsInLayer(1)->begin(); neuron != getNeuronsInLayer(1)->end(); neuron++)
	{
		// Go through all effernetEdges of this neuron
		std::vector<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
		for (std::vector<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
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
	// Go through all neurons in the second layer
	for (std::vector<AbstractNeuron*>::iterator neuron = getNeuronsInLayer(1)->begin(); neuron != getNeuronsInLayer(1)->end(); neuron++)
	{
		// Extract the center vector
		std::vector<float>* t = dynamic_cast<RBFThreshold*>((dynamic_cast<StandardNeuron*>(*neuron))->getThreshold())->getCenterVector();
		// Put in random values
		(*t)[0] = (float)rand() / RAND_MAX * (randEnd - randStart) + randStart;
		(*t)[1] = (float)rand() / RAND_MAX * (randEnd - randStart) + randStart;
	}	
}
	
void RBFNetwork::randomizeWidths(float randStart, float randEnd)
{
	// Go through all neurons in the second layer
	for (std::vector<AbstractNeuron*>::iterator neuron = getNeuronsInLayer(1)->begin(); neuron != getNeuronsInLayer(1)->end(); neuron++)
	{
		// Set a new random value
		dynamic_cast<RBFThreshold*>((dynamic_cast<StandardNeuron*>(*neuron))->getThreshold())->setWidth((float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
	}
}