// Includes
#include "Examples/MountainCar/MountainCarFactory.hpp"
#include "MountainCarController.hpp"

AbstractCustomSubApp* MountainCarFactory::createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
{
	MountainCarController* controller = new MountainCarController(mainApp, trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string MountainCarFactory::getLabel()
{
	return MountainCarController::getLabel();
}
