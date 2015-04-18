#include "TopologicalOrder.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"

void TopologicalOrder::executeActivation(NetworkTopology &networkTopology)
{
	// Cast the network as an layeredNetwork
	LayeredNetwork& layeredNetwork = dynamic_cast<LayeredNetwork&>(networkTopology);

	// Go through all layers
	for (std::vector<std::vector<Neuron*>>::iterator layer = layeredNetwork.getNeurons()->begin(); layer != layeredNetwork.getNeurons()->end(); layer++)
	{
		// Recalculate Activation of all neurons in the current layer
		for (std::vector<Neuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			(*neuron)->refreshActivation();
		}
	}
}