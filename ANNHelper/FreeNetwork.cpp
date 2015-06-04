#include "FreeNetwork.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "BiasNeuron.hpp"
#include "Edge.hpp"
#include "AbstractNeuronFactory.hpp"
#include "LayeredNetwork.hpp"
#include <exception>

FreeNetworkOptions::FreeNetworkOptions()
{
	neuronFactory = NULL;
	useBiasNeuron = false;
	neuronCount = 0;
}

FreeNetworkOptions::~FreeNetworkOptions()
{
	delete(neuronFactory);
}

FreeNetworkOptions::FreeNetworkOptions(const FreeNetworkOptions &obj)
{
	*this = obj;
	neuronFactory = obj.neuronFactory->getCopy();
}



FreeNetwork::~FreeNetwork()
{
	// Go through all neurons 
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		delete(*neuron);
	}	
}

FreeNetwork::FreeNetwork()
{
}

FreeNetwork::FreeNetwork(FreeNetworkOptions &options_)
{
	// Copy all options
	options.reset(new FreeNetworkOptions(options_));
	// Build the network
	buildNetwork();		
}


void FreeNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs)
{
	// Go through all neurons 
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Set the value in the map to the current activation of the neuron
		neuronOutputs[*neuron] = (*neuron)->getActivation();
	}
	
	// Also consider the bias neuron!
	if (options->useBiasNeuron)
		neuronOutputs[&biasNeuron] = 1;
}

void FreeNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs)
{
	// Go through all neurons 
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Set the value in the map to the current netInput of the neuron
		neuronNetInputs[*neuron] = static_cast<StandardNeuron*>(*neuron)->getNetInput();
	}
}


void FreeNetwork::buildNetwork()
{
	// Check if all given options are correct
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");

	// Clear all neurons
	neurons.clear();

	// Add all neurons
	for (int l = 0; l < options->neuronCount; l++)
	{
		addNeuron(false);			
	}

	// Set input neurons from given indices
	for (std::vector<unsigned int>::iterator inputNeuronIndex = options->inputNeuronsIndices.begin(); inputNeuronIndex != options->inputNeuronsIndices.end(); inputNeuronIndex++)
	{
		inputNeurons.push_back(neurons[*inputNeuronIndex]);
	}

	// Set output neurons from given indices
	for (std::vector<unsigned int>::iterator outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		outputNeurons.push_back(neurons[*outputNeuronIndex]);
	}
}

AbstractNeuron* FreeNetwork::addNeuron(bool refreshNeuronCounters)
{
	StandardNeuron* newNeuron;

	// If its the last layer create a output neuron else an inner neuron
	newNeuron = options->neuronFactory->createInnerNeuron();

	// If bias neuron is used add a edge to it
	if (options->useBiasNeuron)
		newNeuron->addPrevNeuron(&biasNeuron, 1);

	// Add an edge to every neuron of the last layer
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		newNeuron->addNextNeuron(static_cast<StandardNeuron*>(*neuron), 1);
		(*neuron)->addNextNeuron(newNeuron, 1);
	}

	newNeuron->addNextNeuron(newNeuron, 1);

	// Add it to the neuronlist
	neurons.push_back(newNeuron);
	

	// Refresh the neuron counters if needed
	if (refreshNeuronCounters)
		options->neuronCount++;

	return newNeuron;	
}

std::vector<AbstractNeuron*>* FreeNetwork::getInputNeurons()
{
	return &inputNeurons;
}

std::vector<AbstractNeuron*>* FreeNetwork::getOutputNeurons()
{
	// Return the last layer
	return &outputNeurons;
}

std::vector<std::vector<AbstractNeuron*>>* FreeNetwork::getNeurons()
{
	static std::vector<std::vector<AbstractNeuron*>> cachedNeurons(1 , neurons);
	return &cachedNeurons;
}

void FreeNetwork::randomizeWeights(float randStart, float randEnd)
{
	// Go through all neurons
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
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
	

	// If a bias neuron is used also randomize its weights
	if (options->useBiasNeuron)
	{
		// Go through all effernetEdges of the bias neuron
		std::list<Edge*>* efferentEdges = biasNeuron.getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			do{
				// Set the weight to a new random value
				(*edge)->setWeight((float)rand() / RAND_MAX * (randEnd - randStart) + randStart);
			} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
		}		
	}
}

int FreeNetwork::getEdgeCount()
{
	int edgeCounter = 0;

	// Go through all neurons
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Add the count of the efferent edges of the current neuron
		edgeCounter += (*neuron)->getEfferentEdges()->size();
	}
	

	// If a bias neuron is used add also its efferent edges
	edgeCounter += biasNeuron.getEfferentEdges()->size();

	return edgeCounter;
}

void FreeNetwork::resetActivation()
{
	// Go through all neurons 
	for (std::vector<AbstractNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Reset the activation of the current neuron
		(*neuron)->resetActivation();
	}
}

std::unique_ptr<LayeredNetwork> FreeNetwork::unfold(int instanceCount)
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = options->neuronFactory;
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(2);
	layeredNetworkOptions.neuronsPerLayerCount[0] = 0;
	layeredNetworkOptions.neuronsPerLayerCount[1] = options->neuronCount;
	layeredNetworkOptions.useBiasNeuron = options->useBiasNeuron;
	layeredNetworkOptions.outputNeuronsIndices = options->outputNeuronsIndices;
	std::unique_ptr<LayeredNetwork> unfoldedNetwork;

	// Do for every instance
	for (int i = 0; i < instanceCount; i++)
	{ 
	
		LayeredNetwork* layeredNetworkToMerge = new LayeredNetwork(layeredNetworkOptions);	

		
		for (std::vector<unsigned int>::iterator inputNeuronIndex = options->inputNeuronsIndices.begin(); inputNeuronIndex != options->inputNeuronsIndices.end(); inputNeuronIndex++)
		{
			layeredNetworkToMerge->addNeuronIntoLayer(0, (*layeredNetworkToMerge->getNeurons())[1][*inputNeuronIndex], true);
		}	
		

		if (i != 0)
		{
			// Go through all current output neurons of the unfolded network
			for (std::vector<AbstractNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all hidden neurons in the second layer of our new network
				for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = (*layeredNetworkToMerge->getNeurons())[1].begin(); hiddenNeuron != (*layeredNetworkToMerge->getNeurons())[1].end(); hiddenNeuron++)
				{
					// Add a edge from the output to the hidden neuron
					(*outputNeuron)->addNextNeuron(static_cast<StandardNeuron*>(*hiddenNeuron), 1);
				}
			}
		}

		if (i != 0)
		{
			// Merge the new network with our unfoldedNetwork
			unfoldedNetwork->mergeWith(*layeredNetworkToMerge);
			delete(layeredNetworkToMerge);
		}
		else
			unfoldedNetwork.reset(layeredNetworkToMerge);
	}

	// Do for every hidden neuron in this layer
	for (int i = 0; i < options->neuronCount; i++)
	{
		// Create a new input neuron and add it to the input layer of the unfolded network
		// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the current hidden layer
		AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true);
		// Go through all hidden neurons of the first hidden layer in our unfolded network
		for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = (*unfoldedNetwork->getNeurons())[1].begin(); hiddenNeuron != (*unfoldedNetwork->getNeurons())[1].end(); hiddenNeuron++)
		{
			// Add a edge from the new input neuron to the hidden neuron
			newInputNeuron->addNextNeuron(static_cast<StandardNeuron*>(*hiddenNeuron), 1);
		}			
	}
		
	return unfoldedNetwork;
}