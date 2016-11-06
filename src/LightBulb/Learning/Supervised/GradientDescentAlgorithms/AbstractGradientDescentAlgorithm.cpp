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

	AbstractGradientDescentAlgorithm::AbstractGradientDescentAlgorithm(const AbstractGradientDescentAlgorithm& other)
	{
		initialized = other.initialized;
		options.reset(dynamic_cast<AbstractGradientDescentAlgorithmOptions*>(other.options->clone()));
	}

	void swap(AbstractGradientDescentAlgorithm& lhs, AbstractGradientDescentAlgorithm& rhs) noexcept
	{
		using std::swap;
		swap(lhs.initialized, rhs.initialized);
		swap(lhs.options, rhs.options);
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