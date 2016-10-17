// Includes
#include "Examples/MountainCar/MountainCarFactory.hpp"
#include "MountainCarController.hpp"

using namespace LightBulb;

AbstractCustomSubApp* MountainCarFactory::createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent) const
{
	MountainCarController* controller = new MountainCarController(mainApp, trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string MountainCarFactory::getLabel() const
{
	return MountainCarController::getLabel();
}
