#pragma once

#ifndef _TICTACTOEAI_H_
#define _TICTACTOEAI_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

// Forward declarations
class TicTacToe;

class TicTacToeAI : public LightBulb::AbstractDefaultIndividual
{
protected:
	TicTacToe* currentGame;
	void getNNInput(LightBulb::Vector<>& input) override;
	void interpretNNOutput(const LightBulb::Vector<>& output) override;
public:
	TicTacToeAI(LightBulb::FeedForwardNetworkTopologyOptions& options, TicTacToe& ticTacToe_);
	TicTacToeAI() = default;
	~TicTacToeAI();
	void setTicTacToe(TicTacToe& newTicTacToe);
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(TicTacToeAI, LightBulb::AbstractDefaultIndividual);

#endif
