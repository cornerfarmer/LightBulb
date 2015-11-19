// Includes
#include "Examples/TicTacToeKI.hpp"
#include "Examples/TicTacToe.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"

TicTacToeKI::TicTacToeKI(TicTacToe* ticTacToe_)
	: AbstractSimpleEvolutionObject(ticTacToe_, 18, 9)
{
	ticTacToe = ticTacToe_;
}

NeuralNetworkIO<double> TicTacToeKI::getNNInput()
{
	return ticTacToe->getSight();
}

void TicTacToeKI::interpretNNOutput(NeuralNetworkIO<double>* output)
{
	for (int i = 0; i < 9; i++)
	{
		int x = i / 3;
		int y = i % 3;
		if (output->get(0, i) > 0.5)
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

