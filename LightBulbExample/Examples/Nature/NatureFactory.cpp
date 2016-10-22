// Includes
#include "Examples/Nature/NatureFactory.hpp"
#include "NatureController.hpp"

using namespace LightBulb;

AbstractCustomSubApp* NatureFactory::createCustomSupApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan, AbstractWindow& parent) const
{
	NatureController* controller = new NatureController(mainApp, trainingPlan, parent);
	controller->getWindow().Show();
	return controller;
}

std::string NatureFactory::getLabel() const
{
	return NatureController::getLabel();
}
