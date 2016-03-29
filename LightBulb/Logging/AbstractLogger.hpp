#pragma once

#ifndef _ABSTRACTLOGGER_H_
#define _ABSTRACTLOGGER_H_

// Library Includes
#include <string>

// Includes

// Forward declarations

enum LogLevel
{
	LL_HIGH,
	LL_MEDIUM,
	LL_LOW
};

class AbstractLogger
{
private:
protected:
	LogLevel currentLogLevel;
	virtual void outputMessage(std::string message) {};
public:
	virtual ~AbstractLogger() {};
	AbstractLogger(LogLevel currentLogLevel_);
	virtual void log(std::string message, LogLevel level);
};

#endif

