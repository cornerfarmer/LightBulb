// Includes
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
	if (isCalculatorType(CT_GPU))
	{
		
	}
	else
	{
		currentGame->setFieldsFromOutput(output);
	}
}

TicTacToeAI::~TicTacToeAI()
{
}


void TicTacToeAI::setTicTacToe(TicTacToe& newTicTacToe)
{
	currentGame = &newTicTacToe;
}