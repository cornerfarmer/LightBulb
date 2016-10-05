#pragma once

#ifndef _CONSOLELOGGER_H_
#define _CONSOLELOGGER_H_

// Library Includes

// Includes
#include "AbstractLogger.hpp"

namespace LightBulb
{
	/**
	 * \brief Logs all messages to the standard console.
	 */
	class ConsoleLogger : public AbstractLogger
	{
	protected:
		// Inherited:
		void outputMessage(std::string message) override;
	public:
		/**
		 * \brief Creates a new ConsoleLogger
		 * \param logLevel The log level to start with.
		 */
		ConsoleLogger(LogLevel logLevel);
	};
}

#endif

