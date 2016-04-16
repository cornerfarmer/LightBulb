#pragma once

#ifndef _TICTACTOEGAMECONTROLLER_H_
#define _TICTACTOEGAMECONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "TicTacToeGameWindow.hpp"
#include "TicTacToe.hpp"


class TicTacToeGameController : public AbstractCustomSubApp
{
private:
	std::unique_ptr<TicTacToeGameWindow> window;
	TicTacToe* world;
public:
	TicTacToeGameController(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent = NULL);
	TicTacToeGameWindow* getWindow();
	void stopStepMode();
	void startStepMode();
	void doStep();
	static std::string getLabel();
	std::vector<std::vector<int>>* getFields();
	void fieldsChanged(TicTacToe* ticTacToe);
};

#endif
