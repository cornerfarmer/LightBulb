// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/PongEvolution/PongGameFactory.hpp"
#include "PongGameController.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

using namespace LightBulb;

AbstractCustomSubApp* PongGameFactory::createCustomSupApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan, AbstractWindow& parent) const
{
	PongGameController* controller = new PongGameController(mainApp, trainingPlan, parent);
	controller->getWindow().Show();
	return controller;
}

std::string PongGameFactory::getLabel() const
{
	return PongGameController::getLabel();
}
