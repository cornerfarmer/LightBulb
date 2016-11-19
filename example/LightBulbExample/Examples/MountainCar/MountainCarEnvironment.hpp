#pragma once

#ifndef _MOUNTAINCARENVIRONMENT_H_
#define _MOUNTAINCARENVIRONMENT_H_

// Library Includes

// Include
#include <Learning/Reinforcement/AbstractReinforcementEnvironment.hpp>
#include <Examples/PongEvolution/AbstractPongEnvironment.hpp>
#include "MountainCarWindow.hpp"

// Forward declarations

enum MountainCarEvents
{
	EVT_POS_CHANGED
};

class MountainCarEnvironment : public LightBulb::AbstractReinforcementEnvironment, public LightBulb::Observable<MountainCarEvents, MountainCarEnvironment>
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
	MountainCarEnvironment(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	MountainCarEnvironment() = default;
	double doSimulationStep() override;
	std::vector<std::string> getDataSetLabels() const override;
	bool isTerminalState() override;
	double getPosition();
	double getVelocity();
	int getAction();
	void startWatchMode();
	void stopWatchMode();
};


#endif
