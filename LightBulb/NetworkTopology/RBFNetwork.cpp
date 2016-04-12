// Includes
#include "NetworkTopology/RBFNetwork.hpp"
#include "NeuronFactory/DifferentNeuronDescriptionFactory.hpp"
#include "Function/EuclideanDistance.hpp"
#include "Function/GaussianRBFFunction.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include <Neuron/NeuronDescription.hpp>

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
	options.reset(new LayeredNetworkOptions());
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

void RBFNetwork::randomizeWeights(double randStart, double randEnd)
{
	for (auto i = 0; i < weights[0].rows(); i++)
	{
		for (auto j = 0; j < weights[0].cols(); j++)
		{
			do {
				weights[0](i, j) = randGenerator.next() * (randEnd - randStart) + randStart;
			} while (weights[0](i, j) == 0);
		}
	}
}

void RBFNetwork::randomizeCenters(double randStart, double randEnd)
{
	weights[0].setRandom();
	weights[0] *= (randEnd - randStart) + randStart;
}
	
void RBFNetwork::randomizeWidths(double randStart, double randEnd)
{
	// Go through all neurons in the second layer
	for (int neuronIndex = 0; neuronIndex != weights[0].rows(); neuronIndex++)
	{
		// Set a new random width to the neuron
		setWidthOfRBFNeuron(neuronIndex, (double)rand() / RAND_MAX * (randEnd - randStart) + randStart);
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
