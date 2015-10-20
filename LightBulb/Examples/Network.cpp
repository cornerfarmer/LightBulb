// Includes
#include "Examples/Network.hpp"
#include "Examples/NetworkSimulator.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"

Network::Network(NetworkSimulator* networkSimulator_)
	: AbstractSimpleEvolutionObject(networkSimulator_, 1, 8, false)
{
	networkSimulator = networkSimulator_;
	positions.resize(4, std::vector<float>(2));
}

NeuralNetworkIO<double> Network::getNNInput()
{
	NeuralNetworkIO<double> input(1);	
	input.set(0, 0, 1);	
	return input;
}

void Network::interpretNNOutput(EvolutionLearningRule& learningRule, NeuralNetworkIO<double>* output)
{
	for (int p = 0; p < 4; p++)
	{	
		for (int i = 0; i < 2; i++)
		{
			positions[p][i] = output->get(0, p * 2 + i);
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

