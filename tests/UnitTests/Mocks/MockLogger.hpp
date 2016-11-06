#pragma once

#ifndef _MOCKLOGGER_H_
#define _MOCKLOGGER_H_

#include "gmock/gmock.h"
#include <Logging/AbstractLogger.hpp>

class MockLogger : public LightBulb::AbstractLogger
{
public:
	explicit MockLogger()
		: AbstractLogger(LightBulb::LL_HIGH)
	{
	}

	MOCK_METHOD1(outputMessage, void (const std::string&));
	MOCK_METHOD2(log, void (const std::string&, const LightBulb::LogLevel&));
};

#endif
