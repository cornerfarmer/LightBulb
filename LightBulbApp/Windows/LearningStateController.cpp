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
	trainingPlansChanged(trainingPlanRepository);
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

std::vector<std::string> LearningStateController::getDataSetLabels()
{
	return selectedTrainingPlan->getDataSetLabels();
}

int LearningStateController::getTryCount()
{
	return selectedTrainingPlan->getLearningState()->tries;
}

std::string LearningStateController::addDataSet(int tryNumber, int dataSetIndex)
{
	std::string dataSetLabel = selectedTrainingPlan->getDataSetLabels()[dataSetIndex];
	selectedDataSets.push_back(std::make_pair(&selectedTrainingPlan->getLearningState()->dataSets[tryNumber], dataSetLabel));
	return dataSetLabel;
}

std::vector<std::pair<DataSetsPerTry*, std::string>>* LearningStateController::getSelectedDataSets()
{
	return &selectedDataSets;
}

void LearningStateController::removeDataSet(int dataSetIndex)
{
	selectedDataSets.erase(selectedDataSets.begin() + dataSetIndex);
}

std::string LearningStateController::getComparisonDataSetLabel()
{
	return comparisonDataSetLabel;
}

void LearningStateController::setComparisonDataSetLabel(std::string newComparisonDataSetLabel)
{
	comparisonDataSetLabel = newComparisonDataSetLabel;
}

std::string LearningStateController::getLabel()
{
	return "LearningState";
}

std::vector<std::string> LearningStateController::getPossibleComparisonDatasetLabels()
{
	std::vector<std::string> possibilities;
	possibilities.push_back(DEFAULT_COMP_DS);
	for (int i = 0; i < selectedDataSets.size(); i++)
	{
		for (auto dataSetSelection = selectedDataSets[i].first->begin(); dataSetSelection != selectedDataSets[i].first->end(); dataSetSelection++)
		{
			if (std::find(possibilities.begin(), possibilities.end(), dataSetSelection->first) == possibilities.end())
				possibilities.push_back(dataSetSelection->first);
		}
	}
	return possibilities;
}
