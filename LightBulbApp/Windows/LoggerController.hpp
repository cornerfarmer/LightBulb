#pragma once

#ifndef _LOGGERCONTROLLER_H_
#define _LOGGERCONTROLLER_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include "LoggerWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class TrainingWindow;
class TrainingPlanRepository;

class LoggerController : public AbstractSubApp
{
private:
	std::unique_ptr<LoggerWindow> window;
	TrainingPlanRepository* trainingPlanRepository;
	AbstractTrainingPlan* selectedTrainingPlan;
	int lastLogMessageIndex;
	void reloadLog();
	bool logMessagesAdding;
	bool autoScrolling;

protected:
	void prepareClose() override;
public:
	LoggerController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository, AbstractWindow* parent = NULL);
	void show();
	void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
	LoggerWindow* getWindow();
	void setLogLevel(int level);
	void logChanged(AbstractLogger* logger);
	std::vector<std::pair<LogLevel, std::string>>* getMessages();
	LogLevel getLogLevel();
	void setAutoScrolling(bool newAutoScrolling);
	bool isAutoScrolling();
	static std::string getLabel();
	void selectTrainingPlan(int trainingPlanIndex);
	void logMessagesAddingFinished();
};

#endif
