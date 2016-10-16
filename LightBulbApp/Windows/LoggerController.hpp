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

namespace LightBulb
{
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
		LoggerController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository, AbstractWindow* parent = nullptr);
		void show();
		void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans() const;
		LoggerWindow* getWindow();
		void setLogLevel(int level);
		void logChanged(AbstractLogger* logger);
		const std::vector<std::pair<LogLevel, std::string>>* getMessages() const;
		const LogLevel& getLogLevel() const;
		void setAutoScrolling(bool newAutoScrolling);
		bool isAutoScrolling() const;
		static const std::string& getLabel();
		void selectTrainingPlan(int trainingPlanIndex);
		void logMessagesAddingFinished();
	};
}

#endif
