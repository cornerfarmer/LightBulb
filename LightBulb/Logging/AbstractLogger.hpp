#pragma once

#ifndef _ABSTRACTLOGGER_H_
#define _ABSTRACTLOGGER_H_

// Library Includes
#include <string>
#include <Event/Observable.hpp>

// Includes
#include "IO/EnumSerialization.hpp"

// Forward declarations

enum LogLevel
{
	LL_HIGH,
	LL_MEDIUM,
	LL_LOW
};


enum LoggerEvents
{
	EVT_LG_LOGADDED
};

class AbstractLogger : public LightBulb::Observable<LoggerEvents, AbstractLogger>
{
private:
protected:
	LogLevel currentLogLevel;
	virtual void outputMessage(std::string message) {};
public:
	virtual ~AbstractLogger() {};
	AbstractLogger(LogLevel currentLogLevel_);
	virtual void log(std::string message, LogLevel level);
	void setLogLevel(LogLevel level);
	LogLevel getLogLevel();
};

#endif

