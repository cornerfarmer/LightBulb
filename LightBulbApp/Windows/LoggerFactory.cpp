// Includes
#include "Windows/LoggerFactory.hpp"
#include "LoggerController.hpp"

AbstractSubApp* LoggerFactory::createWindow(AbstractWindow* parent)
{
	LoggerController* controller = new LoggerController(parent);
	controller->getWindow()->Show();
	return controller;
}

std::string LoggerFactory::getLabel()
{
	return LoggerController::getLabel();
}
