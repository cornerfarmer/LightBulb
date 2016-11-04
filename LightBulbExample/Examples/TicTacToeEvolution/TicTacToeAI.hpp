#pragma once

#ifndef _TICTACTOEKI_H_
#define _TICTACTOEKI_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class TicTacToe;

class TicTacToeAI : public LightBulb::AbstractSimpleEvolutionObject
{
protected:
	TicTacToe* currentGame;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	TicTacToeAI(LightBulb::FeedForwardNetworkTopologyOptions& options, TicTacToe& ticTacToe_);
	TicTacToeAI() = default;
	~TicTacToeAI();
	void setTicTacToe(TicTacToe& newTicTacToe);
};

USE_PARENT_SERIALIZATION(TicTacToeAI, LightBulb::AbstractSimpleEvolutionObject);

#endif
