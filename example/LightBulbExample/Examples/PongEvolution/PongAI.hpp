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
	void getNNInput(LightBulb::Vector<>& input) override;
	void interpretNNOutput(const LightBulb::Vector<>& output) override;
public:
	PongAI(LightBulb::FeedForwardNetworkTopologyOptions& options, Pong& pong_);
	PongAI() = default;
	void setPong(Pong& currentGame_);
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(PongAI, LightBulb::AbstractDefaultIndividual);

#endif
