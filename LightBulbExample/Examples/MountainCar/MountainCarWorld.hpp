#pragma once

#ifndef _MOUNTAINCARWORLD_H_
#define _MOUNTAINCARWORLD_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementWorld.hpp>
#include <Examples/PongEvolution/AbstractPongWorld.hpp>
#include "MountainCarWindow.hpp"

// Forward declarations

enum MountainCarEvents
{
	EVT_POS_CHANGED
};

class MountainCarWorld : public AbstractReinforcementWorld, public LightBulb::Observable<MountainCarEvents, MountainCarWorld>
{
private:
	double pos;
	double vel;
	int action;
	bool watchMode;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	MountainCarWorld(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	MountainCarWorld() = default;
	double doSimulationStep() override;
	std::vector<std::string> getDataSetLabels() override;
	bool isTerminalState() override;
	double getPosition();
	double getVelocity();
	int getAction();
	void startWatchMode();
	void stopWatchMode();
};


#endif
