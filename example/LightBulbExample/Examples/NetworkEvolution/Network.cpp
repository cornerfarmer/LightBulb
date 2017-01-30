// Includes
#include "Examples/NetworkEvolution/Network.hpp"
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include <LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/Function/ActivationFunction/IdentityFunction.hpp>
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>

using namespace LightBulb;

Network::Network(NetworkSimulator& networkSimulator_)
	: AbstractDefaultIndividual(networkSimulator_)
{
	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(8);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}

void Network::getNNInput(LightBulb::Vector<>& input)
{
	if (input.getEigenValue().size() != 1) {
		input.getEigenValueForEditing().resize(1);
		input.getEigenValueForEditing()[0] = 1;
	}
}

void Network::interpretNNOutput(const LightBulb::Vector<>& output)
{
	positions = output;
}


const Vector<>& Network::getPositions() const
{
	return positions;
}

Network::~Network()
{
}

