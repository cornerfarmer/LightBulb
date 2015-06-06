#include "RecurrentLayeredNetwork.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNeuron.hpp"
#include "Edge.hpp"
#include <list>

RecurrentLayeredNetwork::RecurrentLayeredNetwork(RecurrentLayeredNetworkOptions& options_)
{
	// Copy all options
	options.reset(new RecurrentLayeredNetworkOptions(options_));

	// Build the network
	buildNetwork();

	// Build all recurrent stuff
	buildRecurrentConnections();
}

void RecurrentLayeredNetwork::buildRecurrentConnections()
{
	// If we should connect ouput neurons with input neurons
	if (getOptions()->connectOutputWithInnerNeurons)
	{
		// Go through all output neurons
		for (std::vector<StandardNeuron*>::iterator outputNeuron = neurons.back().begin(); outputNeuron != neurons.back().end(); outputNeuron++)
		{
			// Go through all neurons in the first inner layer
			for (std::vector<StandardNeuron*>::iterator innerNeuron = neurons.front().begin(); innerNeuron != neurons.front().end(); innerNeuron++)
			{
				(*outputNeuron)->addNextNeuron(*innerNeuron, 1); // Add a connection from the output to the inner neuron
			}
		}
	}
	
	// If we should self connect all hidden layers
	if (getOptions()->selfConnectHiddenLayers)
	{
		// Go through all hidden layers
		for (int layerIndex = 0; layerIndex < neurons.size() - 2; layerIndex++)
		{
			// Go through all neurons in the current hidden layer
			for (std::vector<StandardNeuron*>::iterator hiddenNeuron = neurons[layerIndex].begin(); hiddenNeuron != neurons[layerIndex].end(); hiddenNeuron++)
			{
				// Go through all other hidden neurons in the current layer (it can be the same neuron)
				for (std::vector<StandardNeuron*>::iterator otherHiddenNeuron = neurons[layerIndex].begin(); otherHiddenNeuron != neurons[layerIndex].end(); otherHiddenNeuron++)
				{
					// Add a connection from the current hidden neuron to the other one
					(*hiddenNeuron)->addNextNeuron(*otherHiddenNeuron, 1); 
				}
			}
		}
	}
	
	// If we should self connect the output layer
	if (getOptions()->selfConnectOutputLayers)
	{
		// Go through all output neurons
		for (std::vector<StandardNeuron*>::iterator outputNeuron = neurons.back().begin(); outputNeuron != neurons.back().end(); outputNeuron++)
		{
			// Go through all other output neurons in the same layer
			for (std::vector<StandardNeuron*>::iterator otherOutputNeuron = neurons.back().begin(); otherOutputNeuron != neurons.back().end(); otherOutputNeuron++)
			{
				// Add a connection from the current output neuron to the other one
				(*outputNeuron)->addNextNeuron(*otherOutputNeuron, 1); 
			}
		}		
	}
}

RecurrentLayeredNetworkOptions* RecurrentLayeredNetwork::getOptions()
{
	return static_cast<RecurrentLayeredNetworkOptions*>(options.get());
}

std::unique_ptr<LayeredNetwork> RecurrentLayeredNetwork::unfold(int instanceCount)
{
	// Create a new layered network with the same options as we used for this recurrent network
	std::unique_ptr<LayeredNetwork> unfoldedNetwork(new LayeredNetwork(*options));

	// Do for every extra instance
	for (int i = 0; i < instanceCount - 1; i++)
	{
		// Create a new layered network with the same options as we used for this recurrent network
		LayeredNetwork layeredNetworkToMerge(*options);

		// If output neurons are connected with inner neurons
		if (getOptions()->connectOutputWithInnerNeurons)
		{
			// Go through all current output neurons of the unfolded network
			for (std::vector<StandardNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all hidden neurons in the first hidden layer of our new network
				for (std::vector<StandardNeuron*>::iterator hiddenNeuron = (*layeredNetworkToMerge.getNeurons()).front().begin(); hiddenNeuron != (*layeredNetworkToMerge.getNeurons()).front().end(); hiddenNeuron++)
				{
					// Add a edge from the output to the hidden neuron
					(*outputNeuron)->addNextNeuron(*hiddenNeuron, 1);
				}
			}
		}

		// If we should self connect the hidden layers
		if (getOptions()->selfConnectHiddenLayers)
		{
			// Go through all hidden layers of the current and the last layeredNetworkToMerge
			std::vector<std::vector<StandardNeuron*>>::iterator hiddenLayer = unfoldedNetwork->getNeurons()->begin() + i * (getOptions()->neuronsPerLayerCount.size() - 1);
			for (std::vector<std::vector<StandardNeuron*>>::iterator otherHiddenLayer = (*layeredNetworkToMerge.getNeurons()).begin(); otherHiddenLayer + 1 != (*layeredNetworkToMerge.getNeurons()).end(); hiddenLayer++, otherHiddenLayer++)
			{
				// Go through all hidden neurons in the unfolded Network
				for (std::vector<StandardNeuron*>::iterator hiddenNeuron = hiddenLayer->begin(); hiddenNeuron != hiddenLayer->end(); hiddenNeuron++)
				{
					// Go through all hidden neurons in the layeredNetworkToMerge
					for (std::vector<StandardNeuron*>::iterator otherHiddenNeuron = otherHiddenLayer->begin(); otherHiddenNeuron != otherHiddenLayer->end(); otherHiddenNeuron++)
					{
						// Add a edge from the hidden to the other hidden neuron
						(*hiddenNeuron)->addNextNeuron(*otherHiddenNeuron, 1);
					}
				}
			}
		}

		
		// If we should self connect the output layer
		if (getOptions()->selfConnectOutputLayers)
		{
			// Go through all current output neurons of the unfolded network
			for (std::vector<StandardNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all output neurons of the layeredNetworkToMerge
				for (std::vector<StandardNeuron*>::iterator outherOutputNeuron = layeredNetworkToMerge.getNeurons()->back().begin(); outherOutputNeuron != layeredNetworkToMerge.getNeurons()->back().end(); outherOutputNeuron++)
				{
					// Add a edge from the output to the other output neuron
					(*outputNeuron)->addNextNeuron(*outherOutputNeuron, 1);					
				}
			}
		}

		// Merge the new network with our unfoldedNetwork
		unfoldedNetwork->mergeWith(layeredNetworkToMerge);
	}

	// If output neurons are connected with inner neurons
	if (getOptions()->connectOutputWithInnerNeurons)
	{
		// Do for every output neuron in the original recurrent network
		for (int i = 0; i < options->neuronsPerLayerCount.back(); i++)
		{
			// Create a new input neuron and add it to the input layer of the unfolded network
			// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the first hidden layer
			AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true);
			// Go through all hidden neurons of the first hidden layer of our unfolded network
			for (std::vector<StandardNeuron*>::iterator hiddenNeuron = (*unfoldedNetwork->getNeurons()).front().begin(); hiddenNeuron != (*unfoldedNetwork->getNeurons()).front().end(); hiddenNeuron++)
			{
				// Add a edge from the new input neuron to the hidden neuron
				newInputNeuron->addNextNeuron(*hiddenNeuron, 1);
			}			
		}
	}

	// If we should self connect the hidden layers
	if (getOptions()->selfConnectHiddenLayers)
	{
		// Do for every hidden layer in the original recurrent network
		for (int l = 0; l < options->neuronsPerLayerCount.size() - 2; l++)
		{
			// Do for every hidden neuron in this layer
			for (int i = 0; i < options->neuronsPerLayerCount[l]; i++)
			{
				// Create a new input neuron and add it to the input layer of the unfolded network
				// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the current hidden layer
				AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true);
				// Go through all hidden neurons of the current hidden layer in our unfolded network
				for (std::vector<StandardNeuron*>::iterator hiddenNeuron = (*unfoldedNetwork->getNeurons())[l].begin(); hiddenNeuron != (*unfoldedNetwork->getNeurons())[l].end(); hiddenNeuron++)
				{
					// Add a edge from the new input neuron to the hidden neuron
					newInputNeuron->addNextNeuron(*hiddenNeuron, 1);
				}			
			}
		}
	}

	// If we should self connect the output layer
	if (getOptions()->selfConnectOutputLayers)
	{
		// Do for every output neuron in the original recurrent network
		for (int i = 0; i < options->neuronsPerLayerCount.back(); i++)
		{
			// Create a new input neuron and add it to the input layer of the unfolded network
			// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the first output layer
			AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true);
			// Go through all output neurons of the first ouput layer of our unfolded network
			for (std::vector<StandardNeuron*>::iterator outputNeuron = (*unfoldedNetwork->getNeurons())[options->neuronsPerLayerCount.size() - 2].begin(); outputNeuron != (*unfoldedNetwork->getNeurons())[options->neuronsPerLayerCount.size() - 2].end(); outputNeuron++)
			{
				// Add a edge from the new input neuron to the hidden neuron
				newInputNeuron->addNextNeuron(*outputNeuron, 1);
			}			
		}
	}

	return unfoldedNetwork;
}

std::unique_ptr<std::map<Edge*, bool>> RecurrentLayeredNetwork::getNonRecurrentEdges()
{
	std::unique_ptr<std::map<Edge*, bool>> nonRecurrentEdges(new std::map<Edge*, bool>());

	// Go through all input neurons
	for (std::vector<AbstractNeuron*>::iterator neuron = inputNeurons.begin(); neuron != inputNeurons.end(); neuron++)
	{
		// Go through all effernetEdges of this neuron
		std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			(*nonRecurrentEdges)[*edge] = false;
		}
	}

	// Go through all hidden/output layers
	int layerIndex = 0;
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = neurons.begin(); layer != neurons.end(); layer++, layerIndex++)
	{
		// Go through all neurons in this layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			// Go through all effernetEdges of this neuron
			std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();
			int edgeIndex = 0;
			for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++, edgeIndex++)
			{
				// If the current layer is the last one or the current edge is not connected to the next layer, this is a recurrent edge
				if (layerIndex == getLayerCount() - 1 || edgeIndex >= neurons[layerIndex + 1].size())
					(*nonRecurrentEdges)[*edge] = false;
				else
					(*nonRecurrentEdges)[*edge] = true;
			}
		}
	}

	// If a bias neuron is used also randomize its weights
	if (options->useBiasNeuron)
	{
		// Go through all effernetEdges of the bias neuron
		std::list<Edge*>* efferentEdges = biasNeuron.getEfferentEdges();
		for (std::list<Edge*>::iterator edge = efferentEdges->begin(); edge != efferentEdges->end(); edge++)
		{
			// A bias neuron can not have any recurrent edges
			(*nonRecurrentEdges)[*edge] = true;
		}		
	}

	return nonRecurrentEdges;
}