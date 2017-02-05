#pragma once

#ifndef _TICTACTOEGAMECONTROLLER_H_
#define _TICTACTOEGAMECONTROLLER_H_

// Includes
#include "LightBulbApp/Windows/AbstractCustomSubApp.hpp"
#include <memory>
#include "TicTacToeGameWindow.hpp"
#include "TicTacToe.hpp"


class TicTacToeGameController : public LightBulb::AbstractCustomSubApp
{
private:
	std::unique_ptr<TicTacToeGameWindow> window;
	TicTacToe* environment;

protected:
	void prepareClose() override;
public:
	TicTacToeGameController(LightBulb::AbstractMainApp& mainApp, LightBulb::AbstractTrainingPlan& trainingPlan, LightBulb::AbstractWindow& parent);
	TicTacToeGameWindow& getWindow();
	void stopStepMode();
	void startStepMode();
	void doStep();
	static std::string getLabel();
	LightBulb::Matrix<int>& getFields();
	void fieldsChanged(TicTacToe& ticTacToe);
};

#endif
