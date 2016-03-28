// Includes
#include "Logging/ConsoleLogger.hpp"
#include <iostream>

void ConsoleLogger::outputMessage(std::string message)
{
	std::cout << message << std::endl;
}

ConsoleLogger::ConsoleLogger(LogLevel logLevel)
	: AbstractLogger(logLevel)
{
}
