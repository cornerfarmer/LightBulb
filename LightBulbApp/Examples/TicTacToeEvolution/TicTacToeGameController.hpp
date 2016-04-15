#pragma once

#ifndef _TICTACTOEGAMECONTROLLER_H_
#define _TICTACTOEGAMECONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "TicTacToeGameWindow.hpp"


class TicTacToeGameController : public AbstractCustomSubApp
{
private:
	std::unique_ptr<TicTacToeGameWindow> window;
public:
	TicTacToeGameController(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent = NULL);
	TicTacToeGameWindow* getWindow();
	static std::string getLabel();
};

#endif
