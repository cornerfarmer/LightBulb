// Includes
#include "Examples/TicTacToeEvolution/TicTacToeKI.hpp"
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>

TicTacToeKI::TicTacToeKI(TicTacToe* ticTacToe_)
	: AbstractSimpleEvolutionObject(ticTacToe_)
{
	LayeredNetworkOptions options;
	options.enableShortcuts = true;
	options.neuronsPerLayerCount.push_back(18);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(9);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	buildNeuralNetwork(options);
}

TicTacToe* TicTacToeKI::getTicTacToe()
{
	return static_cast<TicTacToe*>(world);
}

void TicTacToeKI::getNNInput(std::vector<double>& input)
{
	getTicTacToe()->getSight(input);
}

void TicTacToeKI::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 9; i++)
	{
		int x = i / 3;
		int y = i % 3;
		if (output[i] > 0.5)
		{
			getTicTacToe()->setField(x, y);
			return;
		}
	}
	getTicTacToe()->setIllegalMove(true);
	return;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (getTicTacToe()->isFree(x, y))
			{
				getTicTacToe()->setField(x, y);
				return;
			}
		}
	}
}

TicTacToeKI::~TicTacToeKI()
{
}


void TicTacToeKI::setTicTacToe(TicTacToe* newTicTacToe)
{
	world = newTicTacToe;
}