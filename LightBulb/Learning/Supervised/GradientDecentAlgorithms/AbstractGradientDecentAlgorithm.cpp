// Includes
#include "Learning/Supervised/GradientDecentAlgorithms/AbstractGradientDecentAlgorithm.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	AbstractGradientDecentAlgorithm::AbstractGradientDecentAlgorithm(AbstractGradientDecentAlgorithmOptions* options_)
	{
		options.reset(options_);
		initialized = false;
	}

	void AbstractGradientDecentAlgorithm::initialize(AbstractNetworkTopology* networkTopology)
	{
		initializeAlgorithm(networkTopology);
		initialized = true;
	}

	bool AbstractGradientDecentAlgorithm::isInitialized()
	{
		return initialized;
	}
}
