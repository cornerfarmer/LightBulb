// Includes
#include "LightBulb/Logging/StorageLogger.hpp"

namespace LightBulb
{
	StorageLogger::StorageLogger()
		: AbstractLogger(LL_LOW)
	{
	}

	void StorageLogger::log(const std::string& message, const LogLevel& level)
	{
		messages.push_back(std::pair<LogLevel, std::string>(level, message));
		if (level <= currentLogLevel)
			throwEvent(EVT_LG_LOGADDED, *this);
	}

	const std::vector<std::pair<LogLevel, std::string>>& StorageLogger::getMessages() const
	{
		return messages;
	}
}