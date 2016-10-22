// Includes
#include "Examples/TicTacToeEvolution/TicTacToeKI.hpp"
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>

using namespace LightBulb;

TicTacToeKI::TicTacToeKI(FeedForwardNetworkTopologyOptions& options, TicTacToe& ticTacToe_)
	: AbstractSimpleEvolutionObject(ticTacToe_)
{
	currentGame = &ticTacToe_;
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


void TicTacToeKI::setTicTacToe(TicTacToe& newTicTacToe)
{
	currentGame = &newTicTacToe;
}