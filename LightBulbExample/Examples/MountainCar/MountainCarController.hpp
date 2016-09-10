#pragma once

#ifndef _MOUNTAINCARCONTROLLER_H_
#define _MOUNTAINCARCONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "MountainCarWindow.hpp"
#include "MountainCarWorld.hpp"


class MountainCarController : public LightBulb::AbstractCustomSubApp
{
private:
	std::unique_ptr<MountainCarWindow> window;
	MountainCarWorld* world;
	double position;
	double velocity;
	int action;
protected:
	void prepareClose() override;
public:
	MountainCarController(LightBulb::AbstractMainApp* mainApp, LightBulb::AbstractTrainingPlan* trainingPlan, LightBulb::AbstractWindow* parent = NULL);
	MountainCarWindow* getWindow();
	void stopWatchMode();
	void startWatchMode();
	static std::string getLabel();
	double getPosition();
	double getVelocity();
	int getAction();
	void posChanged(MountainCarWorld* pong);
};

#endif
