
#pragma once

#ifndef _ABSTRACTLOGGABLE_H_
#define _ABSTRACTLOGGABLE_H_

// Include
#include "AbstractLogger.hpp"

// Library Includes
#include <string>

// Forward declarations

// A command which combines a few of the given evolution objects.
class AbstractLoggable
{
private:
	AbstractLogger* logger;
protected:
	void log(std::string message, LogLevel logLevel);
public:
	virtual ~AbstractLoggable()
	{
	}

	virtual void setLogger(AbstractLogger* logger_);
};

#endif
