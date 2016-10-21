#pragma once

#ifndef _PONGREINFORCEMENTWORLD_H_
#define _PONGREINFORCEMENTWORLD_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementWorld.hpp>
#include <Examples/PongEvolution/AbstractPongWorld.hpp>
#include "IO/UseParentSerialization.hpp"

// Forward declarations

#define DATASET_PONG_RATING "Pong rating"

class PongReinforcementWorld : public LightBulb::AbstractReinforcementWorld, public AbstractPongWorld
{
	template <class Archive>
	friend void serialize(Archive& archive, PongReinforcementWorld& world);
	friend struct cereal::LoadAndConstruct<PongReinforcementWorld>;
private:
	int time;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	PongReinforcementWorld(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	PongReinforcementWorld() = default;
	double doSimulationStep() override;
	void executeCompareAI();
	void initializeForLearning() override;
	int rateKI() override;
	std::vector<std::string> getDataSetLabels() const override;
	bool isTerminalState() override;
	void setRandomGenerator(LightBulb::AbstractRandomGenerator& randomGenerator_) override;
};


#include "IO/PongReinforcementWorldIO.hpp"

#endif
