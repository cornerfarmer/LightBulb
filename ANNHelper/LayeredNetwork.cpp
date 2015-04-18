#include "LayeredNetwork.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "BiasNeuron.hpp"
#include "Edge.hpp"
#include "AbstractNeuronFactory.hpp"

LayeredNetwork::~LayeredNetwork()
{

}

LayeredNetwork::LayeredNetwork(const LayeredNetworkOptions_t &options_)
{
	options = options_;

	// Add all neurons
	for (int l = 0; l < options.neuronsPerLayerCount.size(); l++)
	{
		// Add a new list for every layer
		neurons.push_back(std::vector<Neuron*>());

		// Add the neurons to the current layer
		for (int i = 0; i < options.neuronsPerLayerCount[l]; i++)
		{
			// If its the first layer, add InputNeurons, else StandardNeurons
			if (l == 0)
				neurons.back().push_back(options.neuronFactory->createInputNeuron());
			else
			{
				StandardNeuron* newNeuron;

				// If its the last layer create a output neuron else an inner neuron
				if (l == options.neuronsPerLayerCount.size() - 1)
					newNeuron = options.neuronFactory->createOutputNeuron();
				else
					newNeuron = options.neuronFactory->createInnerNeuron();

				neurons.back().push_back(newNeuron);

				// If its not the first layer connect the neuron of the current layer to all neurons of the previous layer
				// Get the last layer
				std::vector<std::vector<Neuron*>>::iterator lastLayer = neurons.end();
				lastLayer--;lastLayer--;

				// Add an edge to every neuron of the last layer
				for (std::vector<Neuron*>::iterator prevNeuron = (*lastLayer).begin(); prevNeuron != (*lastLayer).end(); prevNeuron++)
				{
					newNeuron->addPrevNeuron(*prevNeuron, 0);
				}
			}
		}		

		// If BiasNeurons are used, insert them in every layer except of the last one
		if (options.useBiasNeurons && l < options.neuronsPerLayerCount.size() - 1)
			neurons.back().push_back(new BiasNeuron());
	}

		
}

std::vector<Neuron*>* LayeredNetwork::getInputNeurons()
{
	// Return the first layer
	return &neurons.front();
}

std::vector<Neuron*>* LayeredNetwork::getOutputNeurons()
{
	// Return the last layer
	return &neurons.back();
}

std::vector<Neuron*>* LayeredNetwork::getNeuronsInLayer(int layerNr)
{	
	// Get the first layer
	std::vector<std::vector<Neuron*>>::iterator layer = neurons.begin();
	// Go to the layer with nr
	std::advance(layer, layerNr);

	return &(*layer);
}

int LayeredNetwork::getLayerCount()
{
	return options.neuronsPerLayerCount.size();
}

std::vector<std::vector<Neuron*>>* LayeredNetwork::getNeurons()
{
	return &neurons;
}

void LayeredNetwork::randomizeWeights(float randStart, float randEnd)
{
	// Go through all layers
	for (std::vector<std::vector<Neuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<Neuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
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
	for (std::vector<std::vector<Neuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<Neuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Add the count of the efferent edges of the current neuron
			edgeCounter += (*neuron)->getEfferentEdges()->size();
		}
	}

	return edgeCounter;
}
