// Includes
#include "Logging/AbstractLogger.hpp"

namespace LightBulb
{
	AbstractLogger::AbstractLogger(LogLevel currentLogLevel_)
	{
		currentLogLevel = currentLogLevel_;
	}

	void AbstractLogger::log(std::string message, LogLevel level)
	{
		if (level <= currentLogLevel)
		{
			outputMessage(message);
			throwEvent(EVT_LG_LOGADDED, this);
		}
	}

	void AbstractLogger::setLogLevel(LogLevel level)
	{
		currentLogLevel = level;
	}

	LogLevel AbstractLogger::getLogLevel()
	{
		return currentLogLevel;
	}
}