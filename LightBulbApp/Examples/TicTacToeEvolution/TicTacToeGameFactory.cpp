// Includes
#include "Examples/TicTacToeEvolution//TicTacToeGameFactory.hpp"
#include "TicTacToeGameController.hpp"

AbstractCustomSubApp* TicTacToeGameFactory::createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
{
	TicTacToeGameController* controller = new TicTacToeGameController(mainApp, trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string TicTacToeGameFactory::getLabel()
{
	return TicTacToeGameController::getLabel();
}
