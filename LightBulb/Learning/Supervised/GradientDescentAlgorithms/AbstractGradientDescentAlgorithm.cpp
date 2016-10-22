// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	AbstractGradientDescentAlgorithm::AbstractGradientDescentAlgorithm(AbstractGradientDescentAlgorithmOptions* options_)
	{
		options.reset(options_);
		initialized = false;
	}

	void AbstractGradientDescentAlgorithm::initialize(const AbstractNetworkTopology& networkTopology)
	{
		initializeAlgorithm(networkTopology);
		initialized = true;
	}

	bool AbstractGradientDescentAlgorithm::isInitialized()
	{
		return initialized;
	}
}
