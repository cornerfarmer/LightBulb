#include "LayeredNetwork.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "BiasNeuron.hpp"
#include "Edge.hpp"
#include "AbstractNeuronFactory.hpp"
#include <exception>

LayeredNetworkOptions::LayeredNetworkOptions()
{
	enableShortcuts = false;
	neuronFactory = NULL;
	neuronsPerLayerCount = std::vector<unsigned int>();
	useBiasNeurons = false;
}

LayeredNetworkOptions::~LayeredNetworkOptions()
{
	delete(neuronFactory);
}

LayeredNetworkOptions::LayeredNetworkOptions(const LayeredNetworkOptions &obj)
{
	*this = obj;
	neuronFactory = obj.neuronFactory->getCopy();
}



LayeredNetwork::~LayeredNetwork()
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			delete(*neuron);
		}
	}
}

LayeredNetwork::LayeredNetwork()
{
}

LayeredNetwork::LayeredNetwork(LayeredNetworkOptions_t &options_)
{
	// Copy all options
	options.reset(new LayeredNetworkOptions(options_));

	buildNetwork();		
}

void LayeredNetwork::buildNetwork()
{
	// Check if all given options are correct
	if (getLayerCount() < 2)
		throw std::invalid_argument("A layered network must always contain at least two layers (one input and one output layer)");
	for (int l = 0; l < getLayerCount(); l++)
		if (options->neuronsPerLayerCount[l] == 0)
			throw std::invalid_argument("Every layer has to contain at least one neuron");
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");

	// Clear all neurons
	neurons.clear();

	// Add all neurons
	for (int l = 0; l < getLayerCount(); l++)
	{
		// Add a new list for every layer
		neurons.push_back(std::vector<AbstractNeuron*>());

		// Add the neurons to the current layer
		for (int i = 0; i < options->neuronsPerLayerCount[l]; i++)
		{
			addNeuronIntoLayer(l);
		}		

		// If BiasNeurons are used, insert them in every layer except of the last one
		if (options->useBiasNeurons && l < options->neuronsPerLayerCount.size() - 1)
			neurons.back().push_back(new BiasNeuron());
	}

}

AbstractNeuron* LayeredNetwork::addNeuronIntoLayer(int layerIndex)
{
	// If its the first layer, add InputNeurons, else StandardNeurons
	if (layerIndex == 0)
	{
		InputNeuron* newNeuron = options->neuronFactory->createInputNeuron();
		neurons[layerIndex].push_back(newNeuron);
		return newNeuron;
	}
	else
	{
		StandardNeuron* newNeuron;

		// If its the last layer create a output neuron else an inner neuron
		if (layerIndex == options->neuronsPerLayerCount.size() - 1)
			newNeuron = options->neuronFactory->createOutputNeuron();
		else
			newNeuron = options->neuronFactory->createInnerNeuron();

		neurons[layerIndex].push_back(newNeuron);				

		// Add an edge to every neuron of the last layer
		for (std::vector<AbstractNeuron*>::iterator prevNeuron = getNeuronsInLayer(layerIndex - 1)->begin(); prevNeuron != getNeuronsInLayer(layerIndex - 1)->end(); prevNeuron++)
		{
			newNeuron->addPrevNeuron(*prevNeuron, 1);
		}
		return newNeuron;
	}
}

std::vector<AbstractNeuron*>* LayeredNetwork::getInputNeurons()
{
	// Return the first layer
	return &neurons.front();
}

std::vector<AbstractNeuron*>* LayeredNetwork::getOutputNeurons()
{
	// Return the last layer
	return &neurons.back();
}

std::vector<AbstractNeuron*>* LayeredNetwork::getNeuronsInLayer(int layerIndex)
{	
	// Get the first layer
	std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin();
	// Go to the layer with nr
	std::advance(layer, layerIndex);

	return &(*layer);
}

int LayeredNetwork::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

std::vector<std::vector<AbstractNeuron*>>* LayeredNetwork::getNeurons()
{
	return &neurons;
}

void LayeredNetwork::randomizeWeights(float randStart, float randEnd)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
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
}

int LayeredNetwork::getEdgeCount()
{
	int edgeCounter = 0;
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Add the count of the efferent edges of the current neuron
			edgeCounter += (*neuron)->getEfferentEdges()->size();
		}
	}

	return edgeCounter;
}

bool LayeredNetwork::usesBiasNeurons()
{
	return options->useBiasNeurons;
}