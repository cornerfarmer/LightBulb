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
	useBiasNeuron = false;
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
	std::map<AbstractNeuron*, bool> alreadyDeleted;

	// Go through all inputneurons
	for (std::vector<AbstractNeuron*>::iterator neuron = getInputNeurons()->begin(); neuron != getInputNeurons()->end(); neuron++)
	{
		if (!alreadyDeleted[*neuron])
		{
			delete(*neuron);
			alreadyDeleted[*neuron] = true;
		}
	}

	// Go through all hidden output layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			if (!alreadyDeleted[*neuron])
			{
				delete(*neuron);
				alreadyDeleted[*neuron] = true;
			}
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
	// Build the network
	buildNetwork();		
}

BiasNeuron* LayeredNetwork::getBiasNeuron()
{
	if (options->useBiasNeuron)
		return &biasNeuron;
	else
		return NULL;
}

void LayeredNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs)
{
	// Go through all inputneurons
	for (std::vector<AbstractNeuron*>::iterator neuron = getInputNeurons()->begin(); neuron != getInputNeurons()->end(); neuron++)
	{
		// Set the value in the map to the current activation of the neuron
		neuronOutputs[*neuron] = (*neuron)->getActivation();
	}

	// Go through all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = getNeurons()->begin(); layer != getNeurons()->end(); layer++)
	{
		// Go through all neurons in the current layer
		for (std::vector<StandardNeuron*>::iterator neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			// Set the value in the map to the current activation of the neuron
			neuronOutputs[*neuron] = (*neuron)->getActivation();
		}
	}
	// Also consider the bias neuron!
	if (options->useBiasNeuron)
		neuronOutputs[&biasNeuron] = 1;
}

void LayeredNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs)
{
	// Go through all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = getNeurons()->begin(); layer != getNeurons()->end(); layer++)
	{
		// Go through all neurons in the current layer
		for (std::vector<StandardNeuron*>::iterator neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			neuronNetInputs[*neuron] = (*neuron)->getNetInput();
		}
	}
}


void LayeredNetwork::buildNetwork()
{
	// Check if all given options are correct
	if (getLayerCount() < 2)
		throw std::invalid_argument("A layered network must always contain at least two layers (one input and one output layer)");
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");

	if (options->outputNeuronsIndices.empty())
	{
		for (int i = 0; i < options->neuronsPerLayerCount.back(); i++)
			options->outputNeuronsIndices.push_back(i);
	}
	
	// Clear all neurons
	neurons.clear();

	// Add all neurons
	for (int l = 0; l < getLayerCount(); l++)
	{
		// If it is a hidden layer
		if (l != 0)
		{
			// Add a new list for every hidden layer
			neurons.push_back(std::vector<StandardNeuron*>());
		}

		// Add the neurons to the current layer
		for (int i = 0; i < options->neuronsPerLayerCount[l]; i++)
		{
			addNeuronIntoLayer(l, false, false);
		}		
	}

	rebuildOutputNeurons();
}

void LayeredNetwork::rebuildOutputNeurons()
{
	outputNeurons.clear();

	// Set output neurons from given indices
	for (std::vector<unsigned int>::iterator outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		if (*outputNeuronIndex < neurons.back().size())
			outputNeurons.push_back(neurons.back()[*outputNeuronIndex]);
	}
}

void LayeredNetwork::addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters)
{
	if (layerIndex == 0)
		inputNeurons.push_back(newNeuron);
	else
		neurons[layerIndex - 1].push_back(dynamic_cast<StandardNeuron*>(newNeuron));

	// Refresh the neuron counters if needed
	if (refreshNeuronCounters)
	{
		options->neuronsPerLayerCount[layerIndex] = neurons[layerIndex].size();

		if (layerIndex == options->neuronsPerLayerCount.size() - 1)
			rebuildOutputNeurons();
	}
}

AbstractNeuron* LayeredNetwork::addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer)
{
	AbstractNeuron* newNeuron;

	// If its the first layer, add InputNeurons, else StandardNeurons
	if (layerIndex == 0)
	{
		newNeuron = options->neuronFactory->createInputNeuron();
	}
	else
	{
		// If its the last layer create a output neuron else an inner neuron
		if (layerIndex == options->neuronsPerLayerCount.size() - 1)
			newNeuron = options->neuronFactory->createOutputNeuron();
		else
			newNeuron = options->neuronFactory->createInnerNeuron();	

		// Add an edge to every neuron of the last layer
		for (int l = layerIndex - 1; (l == layerIndex - 1 || options->enableShortcuts) && l >= 0; l--)
		{
			if (l == 0)
			{
				for (std::vector<AbstractNeuron*>::iterator prevNeuron = inputNeurons.begin(); prevNeuron != inputNeurons.end(); prevNeuron++)
				{
					static_cast<StandardNeuron*>(newNeuron)->addPrevNeuron(*prevNeuron, 1);
				}
			}
			else
			{
				for (std::vector<StandardNeuron*>::iterator prevNeuron = neurons[l - 1].begin(); prevNeuron != neurons[l - 1].end(); prevNeuron++)
				{
					static_cast<StandardNeuron*>(newNeuron)->addPrevNeuron(*prevNeuron, 1);
				}
			}
		}

		// If bias neuron is used add a edge to it
		if (options->useBiasNeuron)
			static_cast<StandardNeuron*>(newNeuron)->addPrevNeuron(&biasNeuron, 1);
	}

	if (addEdgesToNextLayer)
	{
		for (int l = layerIndex + 1; (l == layerIndex + 1 || options->enableShortcuts) && l - 1 < neurons.size(); l++)
		{			
			for (std::vector<StandardNeuron*>::iterator nextNeuron = neurons[l - 1].begin(); nextNeuron != neurons[l - 1].end(); nextNeuron++)
			{
				newNeuron->addNextNeuron(*nextNeuron, 1);
			}			
		}
	}
	
	addNeuronIntoLayer(layerIndex, newNeuron, refreshNeuronCounters);

	return newNeuron;
}

void LayeredNetwork::addNewLayer(int layerIndex, int initialNeuronCount)
{
	neurons.insert(neurons.begin() + layerIndex - 1, std::vector<StandardNeuron*>());
	for (int i = 0; i < initialNeuronCount; i++)
		addNeuronIntoLayer(layerIndex, true, true);
}

std::vector<AbstractNeuron*>* LayeredNetwork::getInputNeurons()
{
	// Return the first layer
	return &inputNeurons;
}

std::vector<StandardNeuron*>* LayeredNetwork::getOutputNeurons()
{
	// Return the last layer
	return &outputNeurons;
}

int LayeredNetwork::getLayerCount()
{
	return options->neuronsPerLayerCount.size();
}

std::vector<std::vector<StandardNeuron*>>* LayeredNetwork::getNeurons()
{
	return &neurons;
}

void LayeredNetwork::randomizeWeights(float randStart, float randEnd)
{
	// Go through hidden all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Go through all affernetEdges to this neuron
			std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
			for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
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
	// Go through all hidden layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Add the count of the afferent edges of the current neuron
			edgeCounter += (*neuron)->getAfferentEdges()->size();
		}
	}

	return edgeCounter;
}

void LayeredNetwork::resetActivation()
{
	// Go through all hidden layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Reset the activation of the current neuron
			(*neuron)->resetActivation();
		}
	}
}



void LayeredNetwork::mergeWith(LayeredNetwork& otherNetwork)
{
	// If a bias neuron is used in the other network
	if (otherNetwork.options->useBiasNeuron)
	{
		// Go through all efferent edges of the bias neuron of the other network
		for (std::list<Edge*>::iterator edge = otherNetwork.biasNeuron.getEfferentEdges()->begin(); edge != otherNetwork.biasNeuron.getEfferentEdges()->end(); edge++)
		{
			// If the current network also uses a bias neuron
			if (options->useBiasNeuron)
			{
				// Reconnect the edge to the bias neuron of the current network
				(*edge)->setPrevNeuron(&biasNeuron);
				// Add the edge to the bias neuron of the current network
				biasNeuron.addNextNeuron(*edge);
			}
			else
			{
				// Else just delete the edge from the neuron which is connected with the bias neuron of the other network
				(*edge)->getNextNeuron()->removeAfferentEdge(*edge);
			}
		}
		// Clear all edges of the bias neuron of the other network, so they won't be deleted
		otherNetwork.biasNeuron.getEfferentEdges()->clear();		
	}
	else if (options->useBiasNeuron)
	{
		// Else if the other network does not have a bias neuron, but the current does
		// Go through all hidden layers
		for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
		{
			// Go through all neurons in this layer
			for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
			{
				// Add a edge from our bias neuron to the current neuron in the other network
				biasNeuron.addNextNeuron(*neuron, 1);
			}
		}
	}

	// Insert all input neurons from the otherNetwork into the first layer of this network
	inputNeurons.insert(inputNeurons.end(), otherNetwork.inputNeurons.begin(), otherNetwork.inputNeurons.end());

	// Append every hidden layer from the other network to the layer list of this network
	for (int l = 0; l < otherNetwork.neurons.size(); l++)
	{
		neurons.push_back(otherNetwork.neurons[l]);
	}

	// The outputNeurons of the other network will be our new outputNeurons
	options->outputNeuronsIndices = otherNetwork.options->outputNeuronsIndices;

	// Clear all neurons of other network so they won't be deleted
	otherNetwork.inputNeurons.clear();
	otherNetwork.neurons.clear();

	// Refresh the counters
	refreshNeuronsPerLayerCounters();

	rebuildOutputNeurons();
}

void LayeredNetwork::refreshNeuronsPerLayerCounters()
{
	// Go through all layers
	std::vector<unsigned int>::iterator counter = options->neuronsPerLayerCount.begin();

	// The first counter is for the input layer
	*counter = inputNeurons.size();	
	counter++;

	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++, counter++)
	{
		// If there are more layers than counters
		if (counter == options->neuronsPerLayerCount.end())
		{
			// Add a counter
			options->neuronsPerLayerCount.push_back(0);
			// Set the current counter to the new counter
			counter = options->neuronsPerLayerCount.end() - 1;
		}
		// Set the counter to the current layer size
		*counter = layer->size();		
	}
}

std::unique_ptr<std::map<Edge*, bool>> LayeredNetwork::getNonRecurrentEdges()
{
	// Create a map
	std::unique_ptr<std::map<Edge*, bool>> nonRecurrentEdges(new std::map<Edge*, bool>());

	// Go through all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Go through all afferentEdges of this neuron
			std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
			for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
			{
				// In a feed forward layered network are only non recurrent edges, so always set the value to true
				(*nonRecurrentEdges)[*edge] = true;
			}
		}
	}
	
	return nonRecurrentEdges;
}