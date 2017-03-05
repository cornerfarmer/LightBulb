#pragma once

#ifndef _PONGREINFORCEMENTINDIVIDUAL_H_
#define _PONGREINFORCEMENTINDIVIDUAL_H_

// Library Includes

// Include
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractDefaultReinforcementIndividual.hpp"

// Forward declarations

class PongReinforcementIndividual : public LightBulb::AbstractDefaultReinforcementIndividual
{
private:
protected:
	void interpretNNOutput(LightBulb::Vector<char>& output) override;
public:
	PongReinforcementIndividual(LightBulb::AbstractReinforcementEnvironment* environment_, LightBulb::FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly = false, double epsilon = 0.1);
	PongReinforcementIndividual();
	void isTerminalState(LightBulb::Scalar<char>& isTerminalState) const override;
	void getNNInput(LightBulb::Vector<>& input) const override;
};


USE_PARENT_SINGLE_SERIALIZATION_WITHOUT_NAMESPACE(PongReinforcementIndividual, LightBulb::AbstractDefaultReinforcementIndividual)

#endif
