// Includes
#include "Logging/StorageLogger.hpp"


StorageLogger::StorageLogger()
	: AbstractLogger(LL_LOW)
{
}

void StorageLogger::log(std::string message, LogLevel level)
{
	messages.push_back(std::pair<LogLevel, std::string>(level, message));
	if (level <= currentLogLevel)
		throwEvent(EVT_LG_LOGADDED, this);
}

std::vector<std::pair<LogLevel, std::string>>* StorageLogger::getMessages()
{
	return &messages;
}
