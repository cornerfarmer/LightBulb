// Includes
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
// Library includes
#include <exception>

namespace LightBulb
{
	void TopologicalOrder::executeActivation(AbstractNetworkTopology &networkTopology) const
	{
		// Cast the network as an FeedForwardNetworkTopology
		FeedForwardNetworkTopology* feedForwardNetworkTopology = dynamic_cast<FeedForwardNetworkTopology*>(&networkTopology);

		if (!feedForwardNetworkTopology)
			throw std::invalid_argument("The given networkTopology has to be a FeedForwardNetworkTopology");

		for (int l = 1; l < feedForwardNetworkTopology->getLayerCount(); l++)
		{
			feedForwardNetworkTopology->refreshNetInputsForLayer(l);
			feedForwardNetworkTopology->refreshActivationsForLayer(l);
		}
	}

	AbstractCloneable* TopologicalOrder::clone() const
	{
		return new TopologicalOrder(*this);
	}

	std::unique_ptr<std::map<Edge*, bool>> TopologicalOrder::getSameTimestepEdges(const AbstractNetworkTopology &networkTopology) const
	{
		// Cast the network as an FeedForwardNetworkTopology
		const FeedForwardNetworkTopology* feedForwardNetworkTopology = dynamic_cast<const FeedForwardNetworkTopology*>(&networkTopology);

		// Check if the given networkTopology was a FeedForwardNetworkTopology, else throw a exception
		if (!feedForwardNetworkTopology)
			throw std::invalid_argument("The given networkTopology has to be a FeedForwardNetworkTopology");

		// Only recurrent edges are not in the same time step
		//return feedForwardNetworkTopology->getNonRecurrentEdges();
	}
}