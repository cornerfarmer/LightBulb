// Includes
#include "Examples/TicTacToeEvolution/TicTacToeKI.hpp"
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>

TicTacToeKI::TicTacToeKI(std::vector<unsigned int> neuronsPerLayerCount, TicTacToe* ticTacToe_)
	: AbstractSimpleEvolutionObject(ticTacToe_)
{
	currentGame = ticTacToe_;
	LayeredNetworkOptions options;
	options.enableShortcuts = true;
	options.neuronsPerLayerCount = neuronsPerLayerCount;
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	buildNeuralNetwork(options);
}


void TicTacToeKI::getNNInput(std::vector<double>& input)
{
	currentGame->getSight(input);
}

void TicTacToeKI::interpretNNOutput(std::vector<double>& output)
{
	for (int i = 0; i < 9; i++)
	{
		int x = i / 3;
		int y = i % 3;
		if (output[i] > 0.5)
		{
			currentGame->setField(x, y);
			return;
		}
	}
	currentGame->setIllegalMove(true);
}

TicTacToeKI::~TicTacToeKI()
{
}


void TicTacToeKI::setTicTacToe(TicTacToe* newTicTacToe)
{
	currentGame = newTicTacToe;
}