// Includes
#include "Examples/TicTacToeEvolution/TicTacToeGameController.hpp"
// Library includes
#include <exception>
#include <vector>


TicTacToeGameController::TicTacToeGameController(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
	:AbstractCustomSubApp(trainingPlan)
{
	window.reset(new TicTacToeGameWindow(this, parent));
}

TicTacToeGameWindow* TicTacToeGameController::getWindow()
{
	return window.get();
}

std::string TicTacToeGameController::getLabel()
{
	return "TicTacToeGame";
}
