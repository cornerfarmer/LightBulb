// Includes
#include "LightBulb/Logging/AbstractLoggable.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"

namespace LightBulb
{
	void AbstractLoggable::log(std::string message, LogLevel logLevel)
	{
		if (logger)
			logger->log(message, logLevel);
	}

	AbstractLoggable::AbstractLoggable()
	{
		logger = nullptr;
	}

	void AbstractLoggable::setLogger(AbstractLogger& logger_)
	{
		logger = &logger_;
	}
}
