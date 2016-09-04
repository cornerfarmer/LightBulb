#pragma once

#ifndef _CONSOLELOGGER_H_
#define _CONSOLELOGGER_H_

// Library Includes

// Includes
#include "AbstractLogger.hpp"

// Forward declarations

class ConsoleLogger : public AbstractLogger
{
protected:
	void outputMessage(std::string message) override;
public:
	ConsoleLogger(LogLevel logLevel);
};

#endif

