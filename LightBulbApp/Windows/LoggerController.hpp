#pragma once

#ifndef _LOGGERCONTROLLER_H_
#define _LOGGERCONTROLLER_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <Logging/AbstractLogger.hpp>
#include "LoggerWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class TrainingWindow;

class LoggerController : public AbstractSubApp, public AbstractLogger
{
private:
	std::unique_ptr<LoggerWindow> window;
	std::vector<std::pair<LogLevel, std::string>> messages;
	void reloadLog();
public:
	LoggerController(AbstractWindow* parent = NULL);
	void show();
	LoggerWindow* getWindow();
	void setLogLevel(int level);
	void log(std::string message, LogLevel level);
	static std::string getLabel();
};

#endif
