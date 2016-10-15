// Includes
#include "Logging/ConsoleLogger.hpp"
#include <iostream>

namespace LightBulb
{
	void ConsoleLogger::outputMessage(const std::string& message)
	{
		std::cout << message << std::endl;
	}

	ConsoleLogger::ConsoleLogger(const LogLevel& logLevel)
		: AbstractLogger(logLevel)
	{
	}
}