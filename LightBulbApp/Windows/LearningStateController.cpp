// Includes
#include "Windows/LearningStateController.hpp"
#include <Repositories/NeuralNetworkRepository.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Repositories/TrainingPlanRepository.hpp>
#include <Learning/LearningState.hpp>

LearningStateController::LearningStateController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent)
{
	refreshRate = 100;
	trainingPlanRepository = trainingPlanRepository_;
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &LearningStateController::trainingPlansChanged, this);
	window.reset(new LearningStateWindow(this, parent));
	iterationsSinceLearningStateChanged = 0;
}

LearningStateWindow* LearningStateController::getWindow()
{
	return window.get();
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* LearningStateController::getTrainingPlans()
{
	return trainingPlanRepository->getTrainingPlans();
}

void LearningStateController::trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository)
{
	window->refreshTrainingPlans();
}

void LearningStateController::setSelectedTrainingPlan(int trainingPlanIndex)
{
	selectedTrainingPlan = (*trainingPlanRepository->getTrainingPlans())[trainingPlanIndex].get();
	selectedTrainingPlan->getLearningState()->registerObserver(EVT_LS_DS_CHANGED, &LearningStateController::learningStateChanged, this);
}

AbstractTrainingPlan* LearningStateController::getSelectedTrainingPlan()
{
	return selectedTrainingPlan;
}

void LearningStateController::learningStateChanged(LearningState* learningState)
{		
	if (iterationsSinceLearningStateChanged-- <= 0 && !refreshScheduled)
	{
		refreshScheduled = true;
		wxThreadEvent evt(LSW_EVT_REFRESH_CHART);
		window->GetEventHandler()->QueueEvent(evt.Clone());
		iterationsSinceLearningStateChanged = refreshRate;
	}
}

std::vector<double>* LearningStateController::getDataSet(std::string dataSetLabel)
{
	LearningState* state = selectedTrainingPlan->getLearningState();
	return &state->dataSets[dataSetLabel];
}

void LearningStateController::setRefreshRate(int newRefreshRate)
{
	if (newRefreshRate > 0)
	{
		refreshRate = newRefreshRate;
		iterationsSinceLearningStateChanged = refreshRate;
	}
}

int LearningStateController::getRefreshRate()
{
	return refreshRate;
}

void LearningStateController::refreshFinished()
{
	refreshScheduled = false;
}
