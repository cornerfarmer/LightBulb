// Includes
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes
#include <exception>

void TopologicalOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{

	if (dynamic_cast<LayeredNetwork*>(&networkTopology))
	{

		// Cast the network as an layeredNetwork
		LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

		// Go through all layers
		for (auto layer = layeredNetwork->getNeurons()->begin(); layer != layeredNetwork->getNeurons()->end(); layer++)
		{
			// First recalculate the netInput of all neurons in the current layer
			for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
				(*neuron)->refreshNetInput();
			// Then recalculate the activation of all neurons in the current layer
			for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
				(*neuron)->refreshActivation();
		}
	}
	else if (dynamic_cast<LayeredNetwork*>(&networkTopology))
	{
		// Cast the network as an layeredNetwork
		LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

		for (int l = 1; l < layeredNetwork->getLayerCount(); l++)
		{
			layeredNetwork->refreshNetInputsForLayer(l);
			layeredNetwork->refreshActivationsForLayer(l);
		}
	}
	else
		throw std::invalid_argument("The given networkTopology has to be a layeredNetwork");
}

AbstractActivationOrder* TopologicalOrder::getCopy()
{
	return new TopologicalOrder(*this);
}

std::unique_ptr<std::map<Edge*, bool>> TopologicalOrder::getSameTimestepEdges(AbstractNetworkTopology &networkTopology)
{
	// Cast the network as an layeredNetwork
	LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

	// Check if the given networkTopology was a layeredNetwork, else throw a exception
	if (!layeredNetwork)
		throw std::invalid_argument("The given networkTopology has to be a layeredNetwork");

	// Only recurrent edges are not in the same time step
	return layeredNetwork->getNonRecurrentEdges();
}
