// Includes
#include "Windows/LoggerFactory.hpp"
#include "LoggerController.hpp"

namespace LightBulb
{
	LoggerFactory::LoggerFactory(TrainingPlanRepository* trainingPlanRepository_)
	{
		trainingPlanRepository = trainingPlanRepository_;
	}

	AbstractSubApp* LoggerFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent)
	{
		LoggerController* controller = new LoggerController(mainApp, trainingPlanRepository, parent);
		controller->getWindow()->Show();
		return controller;
	}

	std::string LoggerFactory::getLabel()
	{
		return LoggerController::getLabel();
	}
}