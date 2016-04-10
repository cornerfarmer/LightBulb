// Includes
#include "Windows/LoggerFactory.hpp"
#include "LoggerController.hpp"

LoggerFactory::LoggerFactory(TrainingPlanRepository* trainingPlanRepository_)
{
	trainingPlanRepository = trainingPlanRepository_;
}

AbstractSubApp* LoggerFactory::createWindow(AbstractWindow* parent)
{
	LoggerController* controller = new LoggerController(trainingPlanRepository, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string LoggerFactory::getLabel()
{
	return LoggerController::getLabel();
}
