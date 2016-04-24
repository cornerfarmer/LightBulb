#pragma once

#ifndef _TICTACTOEKI_H_
#define _TICTACTOEKI_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class EvolutionLearningRule;
class TicTacToe;

// TODO: Rename to AI
class TicTacToeKI : public AbstractSimpleEvolutionObject
{
protected:
	TicTacToe* ticTacToe;
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<double>& output);
public:	
	TicTacToeKI(TicTacToe* ticTacToe_ = NULL);
	~TicTacToeKI();
	void setTicTacToe(TicTacToe* newTicTacToe);
};

USE_PARENT_SERIALIZATION(TicTacToeKI, AbstractSimpleEvolutionObject);

#endif
