// Includes
#include "Windows/LoggerController.hpp"
#include "LoggerWindow.hpp"

LoggerController::LoggerController()
	:AbstractLogger(LL_LOW)
{
	window.reset(new LoggerWindow(this));
}

void LoggerController::show()
{
	window->Show();
}

void LoggerController::outputMessage(std::string message)
{
	window->addLogMessage(message);
}
