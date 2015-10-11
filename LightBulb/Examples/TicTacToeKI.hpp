#pragma once

#ifndef _TICTACTOEKI_H_
#define _TICTACTOEKI_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"

// Forward declarations
class EvolutionLearningRule;
class TicTacToe;

class TicTacToeKI : public AbstractSimpleEvolutionObject
{
protected:
	TicTacToe* ticTacToe;
	NeuralNetworkIO<double> getNNInput();
	void interpretNNOutput(EvolutionLearningRule& learningRule, NeuralNetworkIO<double>* output);
public:	
	TicTacToeKI(TicTacToe* ticTacToe_);
	~TicTacToeKI();
};
#endif