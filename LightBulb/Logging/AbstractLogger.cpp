// Includes
#include "Logging/AbstractLogger.hpp"

AbstractLogger::AbstractLogger(LogLevel currentLogLevel_)
{
	currentLogLevel = currentLogLevel_;
}

void AbstractLogger::log(std::string message, LogLevel level)
{
	if (level <= currentLogLevel)
		outputMessage(message);
}
