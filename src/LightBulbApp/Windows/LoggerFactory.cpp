// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/LoggerFactory.hpp"
#include "LightBulbApp/Windows/LoggerController.hpp"

namespace LightBulb
{
	LoggerFactory::LoggerFactory(TrainingPlanRepository& trainingPlanRepository_)
	{
		trainingPlanRepository = &trainingPlanRepository_;
	}

	AbstractSubApp* LoggerFactory::createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const
	{
		LoggerController* controller = new LoggerController(mainApp, *trainingPlanRepository, parent);
		controller->getWindow().Show();
		return controller;
	}

	std::string LoggerFactory::getLabel() const
	{
		return LoggerController::getLabel();
	}
}