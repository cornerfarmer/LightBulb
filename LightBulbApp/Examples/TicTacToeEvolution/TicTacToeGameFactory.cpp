// Includes
#include "Examples/TicTacToeEvolution//TicTacToeGameFactory.hpp"
#include "TicTacToeGameController.hpp"

AbstractCustomSubApp* TicTacToeGameFactory::createCustomSupApp(AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
{
	TicTacToeGameController* controller = new TicTacToeGameController(trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string TicTacToeGameFactory::getLabel()
{
	return TicTacToeGameController::getLabel();
}
