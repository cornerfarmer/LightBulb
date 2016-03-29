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

LoggerWindow* LoggerController::getWindow()
{
	return window.get();
}

void LoggerController::setLogLevel(int level)
{
	currentLogLevel = (LogLevel)level;
	reloadLog();
}

void LoggerController::log(std::string message, LogLevel level)
{
	if (level <= currentLogLevel)
		window->addLogMessage(message);
	messages.push_back(std::pair<LogLevel, std::string>(level, message));
}


void LoggerController::reloadLog()
{
	window->clearLog();
	for (auto message = messages.begin(); message != messages.end(); message++)
	{
		if (message->first <= currentLogLevel)
			window->addLogMessage(message->second);
	}
}

