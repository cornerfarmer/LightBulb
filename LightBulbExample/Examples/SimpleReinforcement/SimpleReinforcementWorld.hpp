#pragma once

#ifndef _SIMPLEREINFORCEMENTWORLD_H_
#define _SIMPLEREINFORCEMENTWORLD_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementWorld.hpp>
#include <Examples/PongEvolution/AbstractPongWorld.hpp>

// Forward declarations


class SimpleReinforcementWorld : public AbstractReinforcementWorld
{
private:
	bool expectedOutput;
	double rating;
	int round;
protected:
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<bool>& output);
public:
	SimpleReinforcementWorld(LayeredNetworkOptions& options_);
	SimpleReinforcementWorld() = default;
	double doSimulationStep();
	std::vector<std::string> getDataSetLabels();
};


#endif
