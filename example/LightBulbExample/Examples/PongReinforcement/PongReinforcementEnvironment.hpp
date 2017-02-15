#pragma once

#ifndef _PONGREINFORCEMENTENVIRONMENT_H_
#define _PONGREINFORCEMENTENVIRONMENT_H_

// Library Includes

// Include
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "Examples/PongEvolution/AbstractPongEnvironment.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

// Forward declarations

#define DATASET_PONG_RATING "Pong rating"

class PongReinforcementEnvironment : public LightBulb::AbstractReinforcementEnvironment, public AbstractPongEnvironment
{
	template <class Archive>
	friend void serialize(Archive& archive, PongReinforcementEnvironment& environment);
	friend struct cereal::LoadAndConstruct<PongReinforcementEnvironment>;
private:
	LightBulb::Scalar<int> time;
	LightBulb::Scalar<>* rewardTmp;
	bool inSimulationPhase;
protected:
	void getNNInput(LightBulb::Vector<>& input) override;
	void interpretNNOutput(LightBulb::Vector<char>& output) override;
public:
	PongReinforcementEnvironment(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	PongReinforcementEnvironment() = default;
	void doSimulationStep(LightBulb::Scalar<>& reward) override;
	void executeCompareAI();
	void initializeForLearning() override;
	std::vector<std::string> getDataSetLabels() const override;
	void isTerminalState(LightBulb::Scalar<char>& isTerminalState) override;
	void setRandomGenerator(LightBulb::AbstractRandomGenerator& randomGenerator_) override;
};


#include "IO/PongReinforcementEnvironmentIO.hpp"

#endif
