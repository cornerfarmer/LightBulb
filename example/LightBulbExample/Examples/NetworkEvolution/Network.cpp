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
	positions.resize(4, std::vector<float>(2));

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(8);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}

void Network::getNNInput(LightBulb::Vector<>& input)
{
	input.getEigenValueForEditing().resize(1);
	input.getEigenValueForEditing()[0] = 1;
}

void Network::interpretNNOutput(const LightBulb::Vector<>& output)
{
	for (int p = 0; p < 4; p++)
	{	
		for (int i = 0; i < 2; i++)
		{
			positions[p][i] = output.getEigenValue()[p * 2 + i];
		}
	}
}


const std::vector<std::vector<float>>& Network::getPositions() const
{
	return positions;
}

Network::~Network()
{
}

