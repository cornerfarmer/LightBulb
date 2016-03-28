// Includes
#include "Windows/LoggerController.hpp"
#include "LoggerWindow.hpp"

LoggerController::LoggerController(AbstractWindow* parent)
	:AbstractLogger(LL_LOW)
{
	window.reset(new LoggerWindow(this, parent));
}

void LoggerController::show()
{
	window->Show();
}

void LoggerController::outputMessage(std::string message)
{
	window->addLogMessage(message);
}

LoggerWindow* LoggerController::getWindow()
{
	return window.get();
}
