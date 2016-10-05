#pragma once

#ifndef _STORAGELOGGER_H_
#define _STORAGELOGGER_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractLogger.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a logger which stores all messages.
	 * \note Does not need a current log level, because ALL messages are stored.
	 */
	class StorageLogger : public AbstractLogger
	{
		template <class Archive>
		friend void serialize(Archive& archive, StorageLogger& storageLogger);
	protected:
		/**
		 * \brief The storage.
		 * \details Loglevel and message text of every message.
		 */
		std::vector<std::pair<LogLevel, std::string>> messages;
	public:
		/**
		 * \brief Creates the logger
		 */
		StorageLogger();
		/**
		 * \brief Returns all messages.
		 * \return All messages.
		 */
		std::vector<std::pair<LogLevel, std::string>>* getMessages();
		// Inherited:
		void log(std::string message, LogLevel level) override;
	};
}

#include "IO/StorageLoggerIO.hpp"

#endif

