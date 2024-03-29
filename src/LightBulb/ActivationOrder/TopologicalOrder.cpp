// Includes
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
// Library includes

namespace LightBulb
{
	void TopologicalOrder::executeActivation(AbstractNetworkTopology &networkTopology, const Vector<>* alternativeInput) const
	{
		// Cast the network as an FeedForwardNetworkTopology
		FeedForwardNetworkTopology* feedForwardNetworkTopology = dynamic_cast<FeedForwardNetworkTopology*>(&networkTopology);

		if (!feedForwardNetworkTopology)
			throw std::invalid_argument("The given networkTopology has to be a FeedForwardNetworkTopology");

		for (int l = 1; l < feedForwardNetworkTopology->getLayerCount(); l++)
		{
			feedForwardNetworkTopology->refreshNetInputsForLayer(l, l == 1 ? alternativeInput : nullptr);
			feedForwardNetworkTopology->refreshActivationsForLayer(l);
		}
	}

	AbstractCloneable* TopologicalOrder::clone() const
	{
		return new TopologicalOrder(*this);
	}

}