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
		for (std::vector<AbstractNeuron*>::iterator outputNeuron = neurons.back().begin(); outputNeuron != neurons.back().end(); outputNeuron++)
		{
			// Go through all neurons in the first inner layer
			for (std::vector<AbstractNeuron*>::iterator innerNeuron = getNeuronsInLayer(1)->begin(); innerNeuron != getNeuronsInLayer(1)->end(); innerNeuron++)
			{
				(*outputNeuron)->addNextNeuron(dynamic_cast<StandardNeuron*>(*innerNeuron), 1); // Add a connection from the output to the inner neuron
			}
		}
	}
	
	// If we should self connect all hidden layers
	if (getOptions()->selfConnectHiddenLayers)
	{
		// Go through all hidden layers
		for (int layerIndex = 1; layerIndex < neurons.size() - 1; layerIndex++)
		{
			// Go through all neurons in the current hidden layer
			for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = getNeuronsInLayer(layerIndex)->begin(); hiddenNeuron != getNeuronsInLayer(layerIndex)->end(); hiddenNeuron++)
			{
				// Go through all other hidden neurons in the current layer (it can be the same)
				for (std::vector<AbstractNeuron*>::iterator otherHiddenNeuron = getNeuronsInLayer(layerIndex)->begin(); otherHiddenNeuron != getNeuronsInLayer(layerIndex)->end(); otherHiddenNeuron++)
				{
					// Add a connection from the current hidden neuron to the other one
					(*hiddenNeuron)->addNextNeuron(dynamic_cast<StandardNeuron*>(*otherHiddenNeuron), 1); 
				}
			}
		}
	}
	
	// If we should self connect the output layer
	if (getOptions()->selfConnectOutputLayers)
	{
		// Go through all output neurons
		for (std::vector<AbstractNeuron*>::iterator outputNeuron = neurons.back().begin(); outputNeuron != neurons.back().end(); outputNeuron++)
		{
			// Go through all other output neurons in the same layer
			for (std::vector<AbstractNeuron*>::iterator otherOutputNeuron = neurons.back().begin(); otherOutputNeuron != neurons.back().end(); otherOutputNeuron++)
			{
				// Add a connection from the current output neuron to the other one
				(*outputNeuron)->addNextNeuron(dynamic_cast<StandardNeuron*>(*otherOutputNeuron), 1); 
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
			for (std::vector<AbstractNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all hidden neurons in the second layer of our new network
				for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = (*layeredNetworkToMerge.getNeurons())[1].begin(); hiddenNeuron != (*layeredNetworkToMerge.getNeurons())[1].end(); hiddenNeuron++)
				{
					// Add a edge from the output to the hidden neuron
					(*outputNeuron)->addNextNeuron(static_cast<StandardNeuron*>(*hiddenNeuron), 1);
				}
			}
		}

		// If we should self connect the hidden layers
		if (getOptions()->selfConnectHiddenLayers)
		{
			// Go through all hidden layers of the current and the last layeredNetworkToMerge
			std::vector<std::vector<AbstractNeuron*>>::iterator hiddenLayer = unfoldedNetwork->getNeurons()->begin() + 1 + i * (getOptions()->neuronsPerLayerCount.size() - 1);
			for (std::vector<std::vector<AbstractNeuron*>>::iterator otherHiddenLayer = (*layeredNetworkToMerge.getNeurons()).begin() + 1; otherHiddenLayer + 1 != (*layeredNetworkToMerge.getNeurons()).end(); hiddenLayer++, otherHiddenLayer++)
			{
				// Go through all hidden neurons in the unfolded Network
				for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = hiddenLayer->begin(); hiddenNeuron != hiddenLayer->end(); hiddenNeuron++)
				{
					// Go through all hidden neurons in the layeredNetworkToMerge
					for (std::vector<AbstractNeuron*>::iterator otherHiddenNeuron = otherHiddenLayer->begin(); otherHiddenNeuron != otherHiddenLayer->end(); otherHiddenNeuron++)
					{
						// Add a edge from the hidden to the other hidden neuron
						(*hiddenNeuron)->addNextNeuron(static_cast<StandardNeuron*>(*otherHiddenNeuron), 1);
					}
				}
			}
		}

		
		// If we should self connect the output layer
		if (getOptions()->selfConnectOutputLayers)
		{
			// Go through all current output neurons of the unfolded network
			for (std::vector<AbstractNeuron*>::iterator outputNeuron = unfoldedNetwork->getNeurons()->back().begin(); outputNeuron != unfoldedNetwork->getNeurons()->back().end(); outputNeuron++)
			{
				// Go through all output neurons of the layeredNetworkToMerge
				for (std::vector<AbstractNeuron*>::iterator outherOutputNeuron = layeredNetworkToMerge.getNeurons()->back().begin(); outherOutputNeuron != layeredNetworkToMerge.getNeurons()->back().end(); outherOutputNeuron++)
				{
					// Add a edge from the output to the other output neuron
					(*outputNeuron)->addNextNeuron(static_cast<StandardNeuron*>(*outherOutputNeuron), 1);					
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
			// Go through all hidden neurons of the second layer of our unfolded network
			for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = (*unfoldedNetwork->getNeurons())[1].begin(); hiddenNeuron != (*unfoldedNetwork->getNeurons())[1].end(); hiddenNeuron++)
			{
				// Add a edge from the new input neuron to the hidden neuron
				newInputNeuron->addNextNeuron(static_cast<StandardNeuron*>(*hiddenNeuron), 1);
			}			
		}
	}

	// If we should self connect the hidden layers
	if (getOptions()->selfConnectHiddenLayers)
	{
		// Do for every hidden layer in the original recurrent network
		for (int l = 1; l < options->neuronsPerLayerCount.size() - 1; l++)
		{
			// Do for every hidden neuron in this layer
			for (int i = 0; i < options->neuronsPerLayerCount[l]; i++)
			{
				// Create a new input neuron and add it to the input layer of the unfolded network
				// This neuron will always have a zero activation and is only used to simulate a recurrent edge for the current hidden layer
				AbstractNeuron* newInputNeuron = unfoldedNetwork->addNeuronIntoLayer(0, true);
				// Go through all hidden neurons of the current hidden layer in our unfolded network
				for (std::vector<AbstractNeuron*>::iterator hiddenNeuron = (*unfoldedNetwork->getNeurons())[l].begin(); hiddenNeuron != (*unfoldedNetwork->getNeurons())[l].end(); hiddenNeuron++)
				{
					// Add a edge from the new input neuron to the hidden neuron
					newInputNeuron->addNextNeuron(static_cast<StandardNeuron*>(*hiddenNeuron), 1);
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
			for (std::vector<AbstractNeuron*>::iterator outputNeuron = (*unfoldedNetwork->getNeurons())[options->neuronsPerLayerCount.size() - 1].begin(); outputNeuron != (*unfoldedNetwork->getNeurons())[options->neuronsPerLayerCount.size() - 1].end(); outputNeuron++)
			{
				// Add a edge from the new input neuron to the hidden neuron
				newInputNeuron->addNextNeuron(static_cast<StandardNeuron*>(*outputNeuron), 1);
			}			
		}
	}

	return unfoldedNetwork;
}
