#pragma once

#ifndef _SIMPLEREINFORCEMENTENVIRONMENT_H_
#define _SIMPLEREINFORCEMENTENVIRONMENT_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementEnvironment.hpp>
#include <Examples/PongEvolution/AbstractPongEnvironment.hpp>

// Forward declarations


class SimpleReinforcementEnvironment : public LightBulb::AbstractReinforcementEnvironment
{
private:
	int posX;
	int posY;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	SimpleReinforcementEnvironment(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	SimpleReinforcementEnvironment() = default;
	double doSimulationStep() override;
	std::vector<std::string> getDataSetLabels() const override;
	bool isTerminalState() override;
};


#endif
