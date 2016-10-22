// Includes
#include "Logging/AbstractLoggable.hpp"

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