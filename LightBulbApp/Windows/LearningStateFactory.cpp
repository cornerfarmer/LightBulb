// Includes
#include "Windows/LearningStateFactory.hpp"
#include "LearningStateController.hpp"

namespace LightBulb
{
	LearningStateFactory::LearningStateFactory(TrainingPlanRepository* trainingPlanRepository_)
	{
		trainingPlanRepository = trainingPlanRepository_;
	}

	AbstractSubApp* LearningStateFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent)
	{
		LearningStateController* controller = new LearningStateController(mainApp, trainingPlanRepository, parent);
		controller->getWindow()->Show();
		return controller;
	}

	std::string LearningStateFactory::getLabel()
	{
		return LearningStateController::getLabel();
	}
}