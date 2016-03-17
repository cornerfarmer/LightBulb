// Includes
#include "Examples/TicTacToeKI.hpp"
#include "Examples/TicTacToe.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>

TicTacToeKI::TicTacToeKI(TicTacToe* ticTacToe_)
	: AbstractSimpleEvolutionObject(ticTacToe_)
{
	ticTacToe = ticTacToe_;

	LayeredNetworkOptions options;
	options.enableShortcuts = true;
	options.neuronsPerLayerCount.push_back(18);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(9);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	buildNeuralNetwork(options);
}

void TicTacToeKI::getNNInput(std::vector<double>& input)
{
	ticTacToe->getSight(input);
}

void TicTacToeKI::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 9; i++)
	{
		int x = i / 3;
		int y = i % 3;
		if (output[i] > 0.5)
		{
			ticTacToe->setField(x, y);
			return;
		}
	}
	ticTacToe->setIllegalMove(true);
	return;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (ticTacToe->isFree(x, y))
			{
				ticTacToe->setField(x, y);
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
	ticTacToe = newTicTacToe;
}