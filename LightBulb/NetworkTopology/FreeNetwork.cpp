#include "NetworkTopology\FreeNetwork.hpp"
#include "Neuron\InputNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\BiasNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "NeuronFactory\AbstractNeuronFactory.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include <exception>

FreeNetworkOptions::FreeNetworkOptions()
{
	neuronFactory = NULL;
	useBiasNeuron = false;
	neuronCount = 0;
	realInputNeurons = false;
	inputNeuronCount = 0;
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
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Delete the neuron
		delete(*neuron);
	}	
	// If the network uses realInput neurons
	if (options->realInputNeurons)
	{
		// Go through all input neurons 
		for (std::vector<AbstractNeuron*>::iterator neuron = inputNeurons.begin(); neuron != inputNeurons.end(); neuron++)
		{
			// Delete the input neuron
			delete(*neuron);
		}	
	}
}

FreeNetwork::FreeNetwork()
{
}

FreeNetwork::FreeNetwork(FreeNetworkOptions &options_)
{
	// Copy all options
	options.reset(new FreeNetworkOptions(options_));

	// Check if all given options are correct
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");
	if (options->realInputNeurons && options->inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (!options->realInputNeurons && options->inputNeuronsIndices.size() == 0)
		throw std::invalid_argument("There has to be at least one index inside the inputNeuronsIndices vector");
	if (options->outputNeuronsIndices.size() == 0)
		throw std::invalid_argument("There has to be at least one index inside the outputNeuronsIndices vector");
	for (std::vector<unsigned int>::iterator inputNeuronIndex = options->inputNeuronsIndices.begin(); !options->realInputNeurons && inputNeuronIndex != options->inputNeuronsIndices.end(); inputNeuronIndex++)
		if (*inputNeuronIndex >= options->neuronCount)
			throw std::invalid_argument("At least one inputNeuronIndex is not valid");
	for (std::vector<unsigned int>::iterator outputNeuronIndex = options->outputNeuronsIndices.begin(); !options->realInputNeurons && outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
		if (*outputNeuronIndex >= options->neuronCount)
			throw std::invalid_argument("At least one outputNeuronIndex is not valid");

	// Build the network
	buildNetwork();		
}


void FreeNetwork::getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs)
{
	// Go through all neurons 
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Set the value in the map to the current activation of the neuron
		neuronOutputs[*neuron] = (*neuron)->getActivation();
	}

	// If the network uses real input neurons
	if (options->realInputNeurons)
	{
		// Go through all input neurons 
		for (std::vector<AbstractNeuron*>::iterator neuron = inputNeurons.begin(); neuron != inputNeurons.end(); neuron++)
		{
			// Set the value in the map to the current activation of the input neuron
			neuronOutputs[*neuron] = (*neuron)->getActivation();
		}	
	}
	
	// Also consider the bias neuron!
	if (options->useBiasNeuron)
		neuronOutputs[&biasNeuron] = 1;
}

void FreeNetwork::getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs)
{
	// Go through all neurons 
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Set the value in the map to the current netInput of the neuron
		neuronNetInputs[*neuron] = (*neuron)->getNetInput();
	}
}


void FreeNetwork::buildNetwork()
{
	// Check if all given options are correct
	if (!options->neuronFactory)
		throw std::invalid_argument("The given neuronFactory is not valid");

	// Clear all neurons
	neurons.clear();
	
	// If the network should use real input neurons
	if (options->realInputNeurons)
	{
		// Create N input neurons
		for (unsigned int i = 0; i < options->inputNeuronCount; i++)
		{
			addNeuron(false, true);
		}
	}

	// Add all neurons
	for (unsigned int l = 0; l < options->neuronCount; l++)
	{
		addNeuron(false);			
	}	

	// If the network does not use real input neurons
	if (!options->realInputNeurons)
	{
		// Set input neurons from given indices
		for (std::vector<unsigned int>::iterator inputNeuronIndex = options->inputNeuronsIndices.begin(); inputNeuronIndex != options->inputNeuronsIndices.end(); inputNeuronIndex++)
		{
			inputNeurons.push_back(neurons[*inputNeuronIndex]);
		}
	}

	// Set output neurons from given indices
	for (std::vector<unsigned int>::iterator outputNeuronIndex = options->outputNeuronsIndices.begin(); outputNeuronIndex != options->outputNeuronsIndices.end(); outputNeuronIndex++)
	{
		outputNeurons.push_back(neurons[*outputNeuronIndex]);
	}
}

AbstractNeuron* FreeNetwork::addNeuron(bool refreshNeuronCounters, bool inputNeuron)
{
	// If this should be a new input neurons
	if (inputNeuron)
	{
		// This is only possible if the network uses real input neurons
		if (options->realInputNeurons)
		{
			InputNeuron* newNeuron;

			// Create a new input neuron
			newNeuron = options->neuronFactory->createInputNeuron();

			// Add an edge to every neuron 
			for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
			{
				newNeuron->addNextNeuron(*neuron, 1);
			}

			// Add it to the input neurons list
			inputNeurons.push_back(newNeuron);	

			// Refresh the neuron counters if needed
			if (refreshNeuronCounters)
				options->inputNeuronCount++;

			return newNeuron;	
		}
		else
			throw std::logic_error("You can not add a InputNeuron if the network does not use real InputNeurons!");
	}
	else
	{
		StandardNeuron* newNeuron;

		// If its the last layer create a output neuron else an inner neuron
		newNeuron = options->neuronFactory->createInnerNeuron();

		if (options->realInputNeurons)
		{
			// Go through all neurons 
			for (std::vector<AbstractNeuron*>::iterator neuron = inputNeurons.begin(); neuron != inputNeurons.end(); neuron++)
			{
				newNeuron->addPrevNeuron(*neuron, 1);
			}
		}

		// If bias neuron is used add a edge to it
		if (options->useBiasNeuron)
			newNeuron->addPrevNeuron(&biasNeuron, 1);

		// Add an edge to every other neuron 
		for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
		{
			newNeuron->addNextNeuron(*neuron, 1);
			(*neuron)->addNextNeuron(newNeuron, 1);
		}		

		// Add a self referencing edge
		newNeuron->addNextNeuron(newNeuron, 1);

		// Add it to the neuronlist
		neurons.push_back(newNeuron);	

		// Refresh the neuron counters if needed
		if (refreshNeuronCounters)
			options->neuronCount++;

		return newNeuron;	
	}
}

std::vector<AbstractNeuron*>* FreeNetwork::getInputNeurons()
{
	return &inputNeurons;
}

std::vector<StandardNeuron*>* FreeNetwork::getOutputNeurons()
{
	// Return the last layer
	return &outputNeurons;
}

std::vector<std::vector<StandardNeuron*>>* FreeNetwork::getNeurons()
{
	static std::vector<std::vector<StandardNeuron*>> cachedNeurons(1 , neurons);
	return &cachedNeurons;
}

void FreeNetwork::randomizeWeights(double randStart, double randEnd)
{
	// Go through all neurons
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Go through all affernetEdges of this neuron
		std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
		for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
		{
			do{
				// Set the weight to a new random value
				(*edge)->randomizeWeight(randStart, randEnd);
			} while ((*edge)->getWeight()==0); // If the new weight is 0 => retry
		}
	}	
}

int FreeNetwork::getEdgeCount()
{
	int edgeCounter = 0;

	// Go through all neurons
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Add the count of the efferent edges of the current neuron
		edgeCounter += (*neuron)->getAfferentEdges()->size();
	}

	return edgeCounter;
}

void FreeNetwork::resetActivation()
{
	// Go through all neurons 
	for (std::vector<StandardNeuron*>::iterator neuron = neurons.begin(); neuron != neurons.end(); neuron++)
	{
		// Reset the activation of the current neuron
		(*neuron)->resetActivation();
	}
}

BiasNeuron* FreeNetwork::getBiasNeuron()
{
	if (options->useBiasNeuron)
		return &biasNeuron;
	else
		return NULL;
}

std::unique_ptr<LayeredNetwork> FreeNetwork::unfold(int instanceCount)
{
	// Create a new layeredNetworkOptions value which will be used for all parts of the new layered network
	LayeredNetworkOptions layeredNetworkOptions;
	// Copy the neuronFactory
	layeredNetworkOptions.neuronFactory = options->neuronFactory;
	// Every part of the unfolded network does only have two layers (one for input and one for all the other neurons)
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(2);
	// If the network does not use real input neurons set the value to zero (it will be filled later), else copy the input neurons count
	if (!options->realInputNeurons)
		layeredNetworkOptions.neuronsPerLayerCount[0] = 0;
	else
		layeredNetworkOptions.neuronsPerLayerCount[0] = options->inputNeuronCount;
	// The second layer holds all the other neurons
	layeredNetworkOptions.neuronsPerLayerCount[1] = options->neuronCount;
	// Copy some more informations
	layeredNetworkOptions.useBiasNeuron = options->useBiasNeuron;
	layeredNetworkOptions.outputNeuronsIndices = options->outputNeuronsIndices;
	
	std::unique_ptr<LayeredNetwork> unfoldedNetwork;

	// Do for every instance
	for (int i = 0; i < instanceCount; i++)
	{ 
		// Create a new part of the unfolded network
		LayeredNetwork* layeredNetworkToMerge = new LayeredNetwork(layeredNetworkOptions);	

		// If the network does not use real input neurons
		if (!options->realInputNeurons)
		{
			// Copy every standard neuron which is also used as a input neuron into the input layer
			for (std::vector<unsigned int>::iterator inputNeuronIndex = options->inputNeuronsIndices.begin(); inputNeuronIndex != options->inputNeuronsIndices.end(); inputNeuronIndex++)
			{
				layeredNetworkToMerge->addNeuronIntoLayer(0, (*layeredNetworkToMerge->getNeurons()).front()[*inputNeuronIndex], true);
			}	
		}
		
		// If this is not the firs part
		if (i != 0)
		{
			// Go through all current output neurons of the unfolded network
			for (std::vector<StandardNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all hidden neurons in the first hidden layer of our new network
				for (std::vector<StandardNeuron*>::iterator hiddenNeuron = (*layeredNetworkToMerge->getNeurons()).front().begin(); hiddenNeuron != (*layeredNetworkToMerge->getNeurons()).front().end(); hiddenNeuron++)
				{
					// Add a edge from the output to the hidden neuron
					(*outputNeuron)->addNextNeuron(*hiddenNeuron, 1);
				}
			}
		}

		// If its not the first part
		if (i != 0)
		{
			// Merge the new network with our unfoldedNetwork
			unfoldedNetwork->mergeWith(*layeredNetworkToMerge);
			delete(layeredNetworkToMerge);
		}
		else // else set the part to be the current unfolded network
			unfoldedNetwork.reset(layeredNetworkToMerge);
	}

	// Do for every neuron 
	for (unsigned int i = 0; i < options->neuronCount; i++)
	{
		// Create a new input neuron and add it to the input layer of the unfolded network
		// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the current hidden layer
		AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true, true);				
	}
		
	return unfoldedNetwork;
}