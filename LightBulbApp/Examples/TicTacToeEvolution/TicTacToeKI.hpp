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
	TicTacToe* currentGame;
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<double>& output);
public:	
	TicTacToeKI(std::vector<unsigned int> neuronsPerLayerCount, TicTacToe* ticTacToe_ = NULL);
	TicTacToeKI() = default;
	~TicTacToeKI();
	void setTicTacToe(TicTacToe* newTicTacToe);
};

USE_PARENT_SERIALIZATION(TicTacToeKI, AbstractSimpleEvolutionObject);

#endif
