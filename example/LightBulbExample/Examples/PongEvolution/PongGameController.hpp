#pragma once

#ifndef _PONGGAMECONTROLLER_H_
#define _PONGGAMECONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "PongGameWindow.hpp"
#include "Pong.hpp"


class PongGameController : public LightBulb::AbstractCustomSubApp
{
private:
	std::unique_ptr<PongGameWindow> window;
	AbstractPongEnvironment* environment;
	PongGameState currentState;
	PongGameProperties properties;
protected:
	void prepareClose() override;
public:
	PongGameController(LightBulb::AbstractMainApp& mainApp, LightBulb::AbstractTrainingPlan& trainingPlan, LightBulb::AbstractWindow& parent);
	PongGameWindow& getWindow();
	void stopWatchMode();
	void startWatchMode();
	static std::string getLabel();
	PongGameState& getState();
	PongGameProperties& getProperties();
	void fieldChanged(AbstractPongEnvironment& pong);
};

#endif
