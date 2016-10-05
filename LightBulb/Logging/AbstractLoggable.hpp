
#pragma once

#ifndef _ABSTRACTLOGGABLE_H_
#define _ABSTRACTLOGGABLE_H_

// Include
#include "AbstractLogger.hpp"

// Library Includes
#include <string>

namespace LightBulb
{
	/**
	 * \brief Describes any class which wants to log something.
	 * \details Before anything can be logged, setLogger() has to be called.
	 */
	class AbstractLoggable
	{
	private:
		AbstractLogger* logger;
	protected:
		/**
		 * \brief Logs a message with the given log level.
		 * \param message The message to log.
		 * \param logLevel The loglevel.
		 */
		void log(std::string message, LogLevel logLevel);
	public:
		virtual ~AbstractLoggable() {};
		/**
		 * \brief Sets the logger.
		 * \param logger_ The logger which should be used for logging.
		 */
		virtual void setLogger(AbstractLogger* logger_);
	};
}

#endif
