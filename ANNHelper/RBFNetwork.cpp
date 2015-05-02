#include "RBFNetwork.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"
#include "RBFThreshold.hpp"
#include "EuclideanDistance.hpp"
#include "GaussianRBFFunction.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "StandardThreshold.hpp"
#include "Edge.hpp"

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
	// Go through all neurons in this layer
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