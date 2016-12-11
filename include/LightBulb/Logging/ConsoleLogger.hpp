#pragma once

#ifndef _CONSOLELOGGER_H_
#define _CONSOLELOGGER_H_

// Library Includes

// Includes
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Logs all messages to the standard console.
	 */
	class ConsoleLogger : public AbstractLogger
	{
	protected:
		// Inherited:
		void outputMessage(const std::string& message) override;
	public:
		/**
		 * \brief Creates a new ConsoleLogger
		 * \param logLevel The log level to start with.
		 */
		ConsoleLogger(const LogLevel& logLevel = LL_LOW);
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::ConsoleLogger, LightBulb::AbstractLogger, LightBulb)

#endif

