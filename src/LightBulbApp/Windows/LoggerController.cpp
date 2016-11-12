// Includes
#include "Windows/LoggerController.hpp"
#include "LoggerWindow.hpp"
#include <Repositories/TrainingPlanRepository.hpp>

namespace LightBulb
{
	LoggerController::LoggerController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository_, AbstractWindow& parent)
		:AbstractSubApp(mainApp)
	{
		autoScrolling = true;
		lastLogMessageIndex = -1;
		selectedTrainingPlan = nullptr;
		trainingPlanRepository = &trainingPlanRepository_;
		trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &LoggerController::trainingPlansChanged, *this);

		window = new LoggerWindow(*this, parent);

		trainingPlansChanged(*trainingPlanRepository);
	}

	void LoggerController::prepareClose()
	{
		trainingPlanRepository->removeObserver(EVT_TP_CHANGED, &LoggerController::trainingPlansChanged, *this);
		if (selectedTrainingPlan)
			selectedTrainingPlan->getLogger().removeObserver(EVT_LG_LOGADDED, &LoggerController::logChanged, *this);
	}

	void LoggerController::trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository)
	{
		window->refreshTrainingPlans();
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& LoggerController::getTrainingPlans() const
	{
		return trainingPlanRepository->getTrainingPlans();
	}

	LoggerWindow& LoggerController::getWindow()
	{
		return *window;
	}

	void LoggerController::setLogLevel(int level)
	{
		selectedTrainingPlan->getLogger().setLogLevel(static_cast<LogLevel>(level));
		reloadLog();
	}

	void LoggerController::logChanged(AbstractLogger& logger)
	{
		if (!logMessagesAdding)
		{
			logMessagesAdding = true;
			wxThreadEvent evt(LW_EVT_ADD_NEW_MSG);
			window->GetEventHandler()->QueueEvent(evt.Clone());
		}
	}

	std::string LoggerController::getLabel()
	{
		return "Logger";
	}

	void LoggerController::selectTrainingPlan(int trainingPlanIndex)
	{
		if (selectedTrainingPlan)
			selectedTrainingPlan->getLogger().removeObserver(EVT_LG_LOGADDED, &LoggerController::logChanged, *this);
		selectedTrainingPlan = trainingPlanRepository->getTrainingPlans()[trainingPlanIndex].get();
		selectedTrainingPlan->getLogger().registerObserver(EVT_LG_LOGADDED, &LoggerController::logChanged, *this);
		reloadLog();
	}

	void LoggerController::logMessagesAddingFinished()
	{
		logMessagesAdding = false;
	}

	const std::vector<std::pair<LogLevel, std::string>>& LoggerController::getMessages() const
	{
		return selectedTrainingPlan->getLogger().getMessages();
	}

	const LogLevel& LoggerController::getLogLevel() const
	{
		return selectedTrainingPlan->getLogger().getLogLevel();
	}

	void LoggerController::setAutoScrolling(bool newAutoScrolling)
	{
		autoScrolling = newAutoScrolling;
	}

	bool LoggerController::isAutoScrolling() const
	{
		return autoScrolling;
	}

	void LoggerController::reloadLog()
	{
		wxThreadEvent evt(LW_EVT_RELOAD_LOG);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}
}