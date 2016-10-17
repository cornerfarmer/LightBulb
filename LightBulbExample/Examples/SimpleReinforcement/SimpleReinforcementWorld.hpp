#pragma once

#ifndef _SIMPLEREINFORCEMENTWORLD_H_
#define _SIMPLEREINFORCEMENTWORLD_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementWorld.hpp>
#include <Examples/PongEvolution/AbstractPongWorld.hpp>

// Forward declarations


class SimpleReinforcementWorld : public LightBulb::AbstractReinforcementWorld
{
private:
	int posX;
	int posY;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	SimpleReinforcementWorld(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	SimpleReinforcementWorld() = default;
	double doSimulationStep() override;
	std::vector<std::string> getDataSetLabels() const override;
	bool isTerminalState() override;
};


#endif
