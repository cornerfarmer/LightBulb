#include "TopologicalOrder.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"
#include <exception>

void TopologicalOrder::executeActivation(NetworkTopology &networkTopology)
{

	// Cast the network as an layeredNetwork
	LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

	// Check if the given networkTopology was a layeredNetwork, else throw a exception
	if (!layeredNetwork)
		throw std::exception();

	// Go through all layers
	for (std::vector<std::vector<Neuron*>>::iterator layer = layeredNetwork->getNeurons()->begin(); layer != layeredNetwork->getNeurons()->end(); layer++)
	{
		// Recalculate Activation of all neurons in the current layer
		for (std::vector<Neuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
		{
			(*neuron)->refreshActivation();
		}
	}
}