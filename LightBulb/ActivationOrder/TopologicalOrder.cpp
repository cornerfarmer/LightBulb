// Includes
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <exception>

void TopologicalOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{
	// Cast the network as an layeredNetwork
	LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

	if (!layeredNetwork)
		throw std::invalid_argument("The given networkTopology has to be a layeredNetwork");

	for (int l = 1; l < layeredNetwork->getLayerCount(); l++)
	{
		layeredNetwork->refreshNetInputsForLayer(l);
		layeredNetwork->refreshActivationsForLayer(l);
	}
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
