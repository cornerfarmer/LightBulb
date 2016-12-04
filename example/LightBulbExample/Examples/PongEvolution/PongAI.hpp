#pragma once

#ifndef _PONGAI_H_
#define _PONGAI_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractDefaultIndividual.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

// Forward declarations
class Pong;

class PongAI : public LightBulb::AbstractDefaultIndividual
{
protected:
	Pong* currentGame;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:
	PongAI(LightBulb::FeedForwardNetworkTopologyOptions& options, Pong& pong_);
	PongAI() = default;
	void setPong(Pong& currentGame_);
};

USE_PARENT_SERIALIZATION(PongAI, LightBulb::AbstractDefaultIndividual, );

#endif
