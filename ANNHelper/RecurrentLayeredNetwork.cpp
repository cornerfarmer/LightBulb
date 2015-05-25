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
		// Go through all outpur neurons
		for (std::vector<AbstractNeuron*>::iterator outputNeuron = neurons.back().begin(); outputNeuron != neurons.back().end(); outputNeuron++)
		{
			// Go through all neurons in the first inner layer
			int innerNeuronIndex = 0;
			for (std::vector<AbstractNeuron*>::iterator innerNeuron = getNeuronsInLayer(1)->begin(); innerNeuron != getNeuronsInLayer(1)->end(); innerNeuron++, innerNeuronIndex++)
			{
				// If this is no bias neuron
				if (innerNeuronIndex + 1 < getNeuronsInLayer(1)->size() || !options->useBiasNeurons)
					(*outputNeuron)->addNextNeuron(dynamic_cast<StandardNeuron*>(*innerNeuron), 1); // Add a connection from the output to the inner neuron
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
	// If ouput neurons are connected with input neurons
	if (getOptions()->connectOutputWithInnerNeurons)
	{
		// Create a new options object and copy the current options into it
		LayeredNetworkOptions layeredNetworkOptions(*options);
		// Only change the neuronsPerLayerCount
		layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(instanceCount * (getLayerCount() - 1) + 1);

		// Set neuron count of the first layer to: original input neuron count * instanceCount
		layeredNetworkOptions.neuronsPerLayerCount[0] = options->neuronsPerLayerCount[0] * instanceCount + options->neuronsPerLayerCount.back();
		// Go through all other layers
		for(int i = 0; i < layeredNetworkOptions.neuronsPerLayerCount.size() - 1; i++)
		{
			// Set the neuron count to the corresponding one in the original settings
			layeredNetworkOptions.neuronsPerLayerCount[i + 1] = options->neuronsPerLayerCount[i % (options->neuronsPerLayerCount.size() - 1) + 1];
		}

		// Create a new unfoldedNetwork from the settings
		std::unique_ptr<LayeredNetwork> unfoldedNetwork(new LayeredNetwork(layeredNetworkOptions));

		// Extract all input neurons
		std::vector<AbstractNeuron*>* inputNeurons = unfoldedNetwork->getInputNeurons();	
		// Go through all input neurons that are not in the original network
		for (int i = 0; i < inputNeurons->size() - 1 - options->neuronsPerLayerCount.back(); i++)
		{
			// Extract the neurons of the layer to which this input neuron should be connected
			std::vector<AbstractNeuron*>* layerToConnect = unfoldedNetwork->getNeuronsInLayer((i / options->neuronsPerLayerCount[0] - 1) * (getLayerCount() - 1) + getLayerCount());
			// Go through all edges of the current input neuron
			std::vector<AbstractNeuron*>::iterator neuronToConnect = layerToConnect->begin();
			for (std::list<Edge*>::iterator edge = (*inputNeurons)[i]->getEfferentEdges()->begin(); edge != (*inputNeurons)[i]->getEfferentEdges()->end(); edge++, neuronToConnect++)
			{
				// Remove the edge from the first inner layer
				(*edge)->getNextNeuron()->removeAfferentEdge(*edge);

				dynamic_cast<StandardNeuron*>(*neuronToConnect)->getAfferentEdges()->push_front(dynamic_cast<StandardNeuron*>(*neuronToConnect)->getAfferentEdges()->back());
				dynamic_cast<StandardNeuron*>(*neuronToConnect)->getAfferentEdges()->pop_back();
				// Set the edge to the corresponding neuron
				(*edge)->setNextNeuron(dynamic_cast<StandardNeuron*>(*neuronToConnect));
				dynamic_cast<StandardNeuron*>(*neuronToConnect)->getAfferentEdges()->push_front(*edge);				
			}
		}

		return unfoldedNetwork;
	}
}