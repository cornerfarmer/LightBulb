#include "RecurrentNetwork.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNeuron.hpp"

RecurrentNetwork::RecurrentNetwork(RecurrentNetworkOptions& options_)
{
	// Copy all options
	options.reset(new RecurrentNetworkOptions(options_));

	// Build the network
	buildNetwork();

	// Build all recurrent stuff
	buildRecurrentConnections();
}

void RecurrentNetwork::buildRecurrentConnections()
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

RecurrentNetworkOptions* RecurrentNetwork::getOptions()
{
	return static_cast<RecurrentNetworkOptions*>(options.get());
}