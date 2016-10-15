#pragma once

#ifndef _TICTACTOEKI_H_
#define _TICTACTOEKI_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class TicTacToe;

// TODO: Rename to AI
class TicTacToeKI : public LightBulb::AbstractSimpleEvolutionObject
{
protected:
	TicTacToe* currentGame;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	TicTacToeKI(LightBulb::FeedForwardNetworkTopologyOptions& options, TicTacToe* ticTacToe_ = nullptr);
	TicTacToeKI() = default;
	~TicTacToeKI();
	void setTicTacToe(TicTacToe* newTicTacToe);
};

USE_PARENT_SERIALIZATION(TicTacToeKI, LightBulb::AbstractSimpleEvolutionObject);

#endif
