// Includes
#include "Windows/LoggerController.hpp"
#include "LoggerWindow.hpp"
#include <Repositories/TrainingPlanRepository.hpp>

LoggerController::LoggerController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent)
{
	autoScrolling = true;
	lastLogMessageIndex = -1;
	selectedTrainingPlan = NULL;
	trainingPlanRepository = trainingPlanRepository_;
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &LoggerController::trainingPlansChanged, this);

	window.reset(new LoggerWindow(this, parent));

	trainingPlansChanged(trainingPlanRepository);
}

void LoggerController::show()
{
	window->Show();
}

void LoggerController::trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository)
{
	window->refreshTrainingPlans();
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* LoggerController::getTrainingPlans()
{
	return trainingPlanRepository->getTrainingPlans();
}

LoggerWindow* LoggerController::getWindow()
{
	return window.get();
}

void LoggerController::setLogLevel(int level)
{
	selectedTrainingPlan->getLogger()->setLogLevel((LogLevel)level);
	reloadLog();
}

void LoggerController::logChanged(AbstractLogger* logger)
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
		selectedTrainingPlan->getLogger()->removeObserver(EVT_LG_LOGADDED, &LoggerController::logChanged, this);
	selectedTrainingPlan = (*trainingPlanRepository->getTrainingPlans())[trainingPlanIndex].get();
	selectedTrainingPlan->getLogger()->registerObserver(EVT_LG_LOGADDED, &LoggerController::logChanged, this);
	reloadLog();
}

void LoggerController::logMessagesAddingFinished()
{
	logMessagesAdding = false;
}

std::vector<std::pair<LogLevel, std::string>>* LoggerController::getMessages()
{
	return selectedTrainingPlan->getLogger()->getMessages();
}

LogLevel LoggerController::getLogLevel()
{
	return selectedTrainingPlan->getLogger()->getLogLevel();
}

void LoggerController::setAutoScrolling(bool newAutoScrolling)
{
	autoScrolling = newAutoScrolling;
}

bool LoggerController::isAutoScrolling()
{
	return autoScrolling;
}

void LoggerController::reloadLog()
{
	wxThreadEvent evt(LW_EVT_RELOAD_LOG);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
