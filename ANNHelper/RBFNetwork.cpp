#include "RBFNetwork.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"
#include "RBFThreshold.hpp"
#include "EuclideanDistance.hpp"
#include "GaussianRBFFunction.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "StandardThreshold.hpp"

RBFNetwork::RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer)
{
	// Create a new options object
	options.reset(new LayeredNetworkOptions());
	// Set all options
	options->enableDirectBackCoupling = false;
	options->enableDirectBackCoupling = false;
	options->enableIndirectBackCoupling = false;
	options->enableLateralBackCoupling = false;
	options->enableShortcuts = false;
	options->useBiasNeurons = false;
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new RBFThreshold(std::vector<float>(neuronCountFirstLayer,0), 0), new EuclideanDistance(), new GaussianRBFFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = neuronCountFirstLayer;
	options->neuronsPerLayerCount[1] = neuronCountSecondLayer;
	options->neuronsPerLayerCount[2] = neuronCountThirdLayer;	

	// Build the network
	buildNetwork();
}
