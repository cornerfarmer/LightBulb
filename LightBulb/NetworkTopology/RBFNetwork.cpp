// Includes
#include "NetworkTopology/RBFNetwork.hpp"
#include "NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "Function/InputFunction/EuclideanDistance.hpp"
#include "Function/ActivationFunction//GaussianRBFFunction.hpp"
#include "Function/InputFunction/WeightedSumFunction.hpp"
#include "Function/ActivationFunction/IdentityFunction.hpp"
#include <NeuronDescription/NeuronDescription.hpp>
#include "Random/AbstractRandomGenerator.hpp"

namespace LightBulb
{
	RBFNetwork::RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer)
	{
		// Check if all given options are correct
		if (neuronCountFirstLayer == 0)
			throw std::invalid_argument("The given neuronCountFirstLayer has to be greater than 0");
		if (neuronCountSecondLayer == 0)
			throw std::invalid_argument("The given neuronCountSecondLayer has to be greater than 0");
		if (neuronCountThirdLayer == 0)
			throw std::invalid_argument("The given neuronCountThirdLayer has to be greater than 0");

		// Create a new options object
		options.reset(new FeedForwardNetworkTopologyOptions());
		// Set all options
		options->enableShortcuts = false;
		// Define thresholds and functions
		options->descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new EuclideanDistance(), new GaussianRBFFunction(&neuronWidths)), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
		// Set the neuronCounts in all three layers
		options->neuronsPerLayerCount = std::vector<unsigned int>(3);
		options->neuronsPerLayerCount[0] = neuronCountFirstLayer;
		options->neuronsPerLayerCount[1] = neuronCountSecondLayer;
		options->neuronsPerLayerCount[2] = neuronCountThirdLayer;
		options->useBiasNeuron = false;
		// Build the network
		buildNetwork();

		neuronWidths = Eigen::VectorXd(neuronCountSecondLayer);
	}

	RBFNetwork::RBFNetwork()
	{
	}

	void RBFNetwork::randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd)
	{
		for (auto i = 0; i < weights[0].rows(); i++)
		{
			for (auto j = 0; j < weights[0].cols(); j++)
			{
				do {
					weights[0](i, j) = randomGenerator->randDouble(randStart, randEnd);
				} while (weights[0](i, j) == 0);
			}
		}
	}

	void RBFNetwork::randomizeCenters(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd)
	{
		weights[0].setRandom();
		weights[0] *= randomGenerator->randDouble(randStart, randEnd);
	}

	void RBFNetwork::randomizeWidths(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd)
	{
		// Go through all neurons in the second layer
		for (int neuronIndex = 0; neuronIndex != weights[0].rows(); neuronIndex++)
		{
			// Set a new random width to the neuron
			setWidthOfRBFNeuron(neuronIndex, randomGenerator->randDouble(randStart, randEnd));
		}
	}

	void RBFNetwork::setCenterOfRBFNeuron(int neuronIndex, std::vector<double> &newCenterPosition)
	{
		// Set the new center position to the neuron with neuronIndex
		auto centerCoordinate = newCenterPosition.begin();
		for (int i = 0; i < weights[0].cols(); i++)
		{
			weights[0](neuronIndex, i) = newCenterPosition[i];
		}
	}

	void RBFNetwork::setWidthOfRBFNeuron(int neuronIndex, double newWidth)
	{
		// Set the new width to the neuron with neuronIndex
		neuronWidths(neuronIndex) = newWidth;
	}

	double RBFNetwork::getWidthOfRBFNeuron(int neuronIndex)
	{
		return neuronWidths(neuronIndex);
	}

	AbstractNetworkTopology* RBFNetwork::clone()
	{
		RBFNetwork* clone = new RBFNetwork();
		clone->copyWeightsFrom(*this);
		clone->neuronWidths = neuronWidths;
		return clone;
	}
}