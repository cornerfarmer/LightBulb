#pragma once

#ifndef _PONGAI_H_
#define _PONGAI_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class EvolutionLearningRule;
class Pong;

class PongAI : public AbstractSimpleEvolutionObject
{
protected:
	Pong* currentGame;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	PongAI(FeedForwardNetworkTopologyOptions& options, Pong* pong_ = NULL);
	PongAI() = default;
	void setPong(Pong* currentGame_);
};

USE_PARENT_SERIALIZATION(PongAI, AbstractSimpleEvolutionObject);

#endif
