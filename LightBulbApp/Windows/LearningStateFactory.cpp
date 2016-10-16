// Includes
#include "Windows/LearningStateFactory.hpp"
#include "LearningStateController.hpp"

namespace LightBulb
{
	LearningStateFactory::LearningStateFactory(TrainingPlanRepository* trainingPlanRepository_)
	{
		trainingPlanRepository = trainingPlanRepository_;
	}

	AbstractSubApp* LearningStateFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) const
	{
		LearningStateController* controller = new LearningStateController(mainApp, trainingPlanRepository, parent);
		controller->getWindow()->Show();
		return controller;
	}

	const std::string& LearningStateFactory::getLabel() const
	{
		return LearningStateController::getLabel();
	}
}