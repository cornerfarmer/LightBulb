// Includes
#include "Logging/AbstractLoggable.hpp"


void AbstractLoggable::log(std::string message, LogLevel logLevel)
{
	if (logger)
		logger->log(message, logLevel);
}

void AbstractLoggable::setLogger(AbstractLogger* logger_)
{
	logger = logger_;
}
