// Includes
#include "Windows/LearningStateFactory.hpp"
#include "LearningStateController.hpp"

LearningStateFactory::LearningStateFactory(TrainingPlanRepository* trainingPlanRepository_)
{
	trainingPlanRepository = trainingPlanRepository_;
}

AbstractSubApp* LearningStateFactory::createSupApp(AbstractWindow* parent)
{
	LearningStateController* controller = new LearningStateController(trainingPlanRepository, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string LearningStateFactory::getLabel()
{
	return LearningStateController::getLabel();
}
