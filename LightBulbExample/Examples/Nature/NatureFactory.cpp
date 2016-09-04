// Includes
#include "Examples/Nature/NatureFactory.hpp"
#include "NatureController.hpp"

AbstractCustomSubApp* NatureFactory::createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent)
{
	NatureController* controller = new NatureController(mainApp, trainingPlan, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string NatureFactory::getLabel()
{
	return NatureController::getLabel();
}
