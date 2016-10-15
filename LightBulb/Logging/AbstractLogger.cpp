// Includes
#include "Logging/AbstractLogger.hpp"

namespace LightBulb
{
	AbstractLogger::AbstractLogger(const LogLevel& currentLogLevel_)
	{
		currentLogLevel = currentLogLevel_;
	}

	void AbstractLogger::log(const std::string& message, const LogLevel& level)
	{
		if (level <= currentLogLevel)
		{
			outputMessage(message);
			throwEvent(EVT_LG_LOGADDED, this);
		}
	}

	void AbstractLogger::setLogLevel(const LogLevel& level)
	{
		currentLogLevel = level;
	}

	const LogLevel& AbstractLogger::getLogLevel() const
	{
		return currentLogLevel;
	}
}