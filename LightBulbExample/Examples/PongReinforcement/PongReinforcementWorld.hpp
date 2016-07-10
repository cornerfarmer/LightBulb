#pragma once

#ifndef _PONGREINFORCEMENTWORLD_H_
#define _PONGREINFORCEMENTWORLD_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementWorld.hpp>
#include <Examples/PongEvolution/PongGame.hpp>
#include <Examples/PongEvolution/AbstractPongWorld.hpp>

// Forward declarations

#define DATASET_PONG_RATING "Pong rating"

class PongReinforcementWorld : public AbstractReinforcementWorld, public AbstractPongWorld
{
private:
	int time;
protected:
	void getNNInput(std::vector<double>& input);
	void interpretNNOutput(std::vector<bool>& output);
public:
	PongReinforcementWorld(LayeredNetworkOptions& options_);
	PongReinforcementWorld() = default;
	double doSimulationStep();
	void executeCompareAI();
	void initializeForLearning();
	int rateKI();
	std::vector<std::string> getDataSetLabels();
};


#endif
