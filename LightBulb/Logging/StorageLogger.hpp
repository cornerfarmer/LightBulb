#pragma once

#ifndef _STORAGELOGGER_H_
#define _STORAGELOGGER_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractLogger.hpp"

// Forward declarations

class StorageLogger : public AbstractLogger
{
	template <class Archive>
	friend void serialize(Archive& archive, StorageLogger& storageLogger);
protected:
	std::vector<std::pair<LogLevel, std::string>> messages;
public:
	StorageLogger();
	void log(std::string message, LogLevel level) override;
	std::vector<std::pair<LogLevel, std::string>>* getMessages();
};

#include "IO/StorageLoggerIO.hpp"

#endif

