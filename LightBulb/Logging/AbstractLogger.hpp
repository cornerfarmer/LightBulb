#pragma once

#ifndef _ABSTRACTLOGGER_H_
#define _ABSTRACTLOGGER_H_

// Library Includes
#include <string>
#include <Event/Observable.hpp>

// Includes

namespace LightBulb
{
	/**
	 * \brief All choosable log levels.
	 */
	enum LogLevel
	{
		/**
		 * \brief High priority.
		 */
		LL_HIGH,
		/**
		* \brief Normal priority.
		*/
		LL_MEDIUM,
		/**
		* \brief Low priority.
		*/
		LL_LOW
	};
	
	/**
	 * \brief All observable events of AbstractLogger.
	 */
	enum LoggerEvents
	{
		/**
		 * \brief Is thrown when a new log message has been added.
		 */
		EVT_LG_LOGADDED
	};

	/**
	 * \brief Describes a logger which can store and/or display messages with different priorities.
	 */
	class AbstractLogger : public Observable<LoggerEvents, AbstractLogger>
	{
	private:
	protected:
		/**
		 * \brief The current log level which should be displayed.
		 * \details Only messages which have the same or a higher priority as the current log level are displayed.
		 */
		LogLevel currentLogLevel;
		/**
		 * \brief Display a new message.
		 * \param message The message text.
		 * \note Is only called for messages which have the same or a higher priority as the current log level.
		 */
		virtual void outputMessage(const std::string& message) {};
	public:
		virtual ~AbstractLogger() {};
		/**
		 * \brief Creates the logger.
		 * \param currentLogLevel_ The log level from the start.
		 */
		AbstractLogger(const LogLevel& currentLogLevel_);
		/**
		 * \brief Log a new message.
		 * \param message The text of the message.
		 * \param level The log level of the message.
		 * \note Only logs messages which have the same or a higher priority as the current log level.
		 */
		virtual void log(const std::string& message, const LogLevel& level);
		/**
		 * \brief Sets a new log level.
		 * \param level The new log level.
		 */
		void setLogLevel(const LogLevel& level);
		/**
		 * \brief Returns the current log level.
		 * \return The current log level.
		 */
		const LogLevel& getLogLevel() const;
	};
}

#endif

