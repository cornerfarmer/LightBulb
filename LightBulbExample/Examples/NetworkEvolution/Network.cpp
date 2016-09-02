// Includes
#include "Examples/NetworkEvolution/Network.hpp"
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include <NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Function/ActivationFunction/IdentityFunction.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/NeuronDescription.hpp>

Network::Network(NetworkSimulator* networkSimulator_)
	: AbstractSimpleEvolutionObject(networkSimulator_)
{
	positions.resize(4, std::vector<float>(2));

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(8);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}

void Network::getNNInput(std::vector<double>& input)
{
	input.resize(1);
	input[0] = 1;
}

void Network::interpretNNOutput(std::vector<double>& output)
{
	for (int p = 0; p < 4; p++)
	{	
		for (int i = 0; i < 2; i++)
		{
			positions[p][i] = output[p * 2 + i];
		}
	}
}


std::vector<std::vector<float>>* Network::getPositions()
{
	return &positions;
}

Network::~Network()
{
}

