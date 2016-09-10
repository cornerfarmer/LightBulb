// Includes
#include "Examples/PongEvolution/PongGameFactory.hpp"
#include "PongGameController.hpp"

using namespace LightBulb;

AbstractCustomSubApp* PongGameFactory::createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
{
	PongGameController* controller = new PongGameController(mainApp, trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string PongGameFactory::getLabel()
{
	return PongGameController::getLabel();
}
