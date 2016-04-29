#pragma once

#ifndef _MOCKLOGGER_H_
#define _MOCKLOGGER_H_

#include "gmock/gmock.h"
#include <Logging/AbstractLogger.hpp>

class MockLogger : public AbstractLogger
{
public:
	explicit MockLogger()
		: AbstractLogger(LL_HIGH)
	{
	}

	MOCK_METHOD1(outputMessage, void (std::string));
	MOCK_METHOD2(log, void (std::string, LogLevel));
};

#endif
