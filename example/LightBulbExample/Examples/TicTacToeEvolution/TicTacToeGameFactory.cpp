// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeGameFactory.hpp"
#include "TicTacToeGameController.hpp"

using namespace LightBulb;

AbstractCustomSubApp* TicTacToeGameFactory::createCustomSupApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan, AbstractWindow& parent) const
{
	TicTacToeGameController* controller = new TicTacToeGameController(mainApp, trainingPlan, parent);
	controller->getWindow().Show();
	return controller;
}

std::string TicTacToeGameFactory::getLabel() const
{
	return TicTacToeGameController::getLabel();
}
