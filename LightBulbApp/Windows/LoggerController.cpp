// Includes
#include "Windows/LoggerController.hpp"
#include "LoggerWindow.hpp"
#include <Repositories/TrainingPlanRepository.hpp>

LoggerController::LoggerController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent)
{
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
	addNewLogMessages();
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

void LoggerController::reloadLog()
{
	lastLogMessageIndex = -1;
	window->clearLog();
	for (auto message = selectedTrainingPlan->getLogger()->getMessages()->begin(); message != selectedTrainingPlan->getLogger()->getMessages()->end(); message++)
	{
		if (message->first <= selectedTrainingPlan->getLogger()->getLogLevel())
			addLogMessage(message->second);
		lastLogMessageIndex++;
	}
}

void LoggerController::addLogMessage(std::string message)
{
	wxThreadEvent evt(LW_EVT_ADD_MSG);
	evt.SetPayload<wxString>(wxString(message).c_str());
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void LoggerController::addNewLogMessages()
{
	auto messages = selectedTrainingPlan->getLogger()->getMessages();
	for (int messageIndex = lastLogMessageIndex + 1; messageIndex < selectedTrainingPlan->getLogger()->getMessages()->size(); messageIndex++)
	{
		if ((*messages)[messageIndex].first <= selectedTrainingPlan->getLogger()->getLogLevel())
			addLogMessage((*messages)[messageIndex].second);
		lastLogMessageIndex++;
	}
}
