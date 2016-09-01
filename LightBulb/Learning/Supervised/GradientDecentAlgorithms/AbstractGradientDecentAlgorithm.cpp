// Includes
#include "Learning/Supervised/GradientDecentAlgorithms/AbstractGradientDecentAlgorithm.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


AbstractGradientDecentAlgorithm::AbstractGradientDecentAlgorithm(AbstractGradientDecentAlgorithmOptions* options_)
{
	options.reset(options_);
	initialized = false;
}

void AbstractGradientDecentAlgorithm::initialize(AbstractNeuralNetwork &neuralNetwork)
{
	initializeAlgorithm(neuralNetwork);
	initialized = true;
}

bool AbstractGradientDecentAlgorithm::isInitialized()
{
	return initialized;
}

