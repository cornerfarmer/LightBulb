// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeAI.hpp"
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

using namespace LightBulb;

TicTacToeAI::TicTacToeAI(FeedForwardNetworkTopologyOptions& options, TicTacToe& ticTacToe_)
	: AbstractDefaultIndividual(ticTacToe_)
{
	currentGame = &ticTacToe_;
	buildNeuralNetwork(options);
}


void TicTacToeAI::getNNInput(LightBulb::Vector<>& input)
{
	currentGame->getSight(input);
}

void TicTacToeAI::interpretNNOutput(const LightBulb::Vector<>& output)
{
	for (int i = 0; i < 9; i++)
	{
		int x = i / 3;
		int y = i % 3;
		if (output.getEigenValue()[i] > 0.5)
		{
			currentGame->setField(x, y);
			return;
		}
	}
	currentGame->setIllegalMove(true);
}

TicTacToeAI::~TicTacToeAI()
{
}


void TicTacToeAI::setTicTacToe(TicTacToe& newTicTacToe)
{
	currentGame = &newTicTacToe;
}