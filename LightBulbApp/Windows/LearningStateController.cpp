// Includes
#include "Windows/LearningStateController.hpp"
#include <Repositories/NeuralNetworkRepository.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Repositories/TrainingPlanRepository.hpp>
#include <Learning/LearningState.hpp>

namespace LightBulb
{
	DataSet& DataSetSelection::getDataSet(std::string otherLabel)
	{
		if (otherLabel == "")
			return trainingPlan->getLearningState().dataSets[tryNumber][label];
		else
			return trainingPlan->getLearningState().dataSets[tryNumber][otherLabel];
	}

	LearningStateController::LearningStateController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository_, AbstractWindow& parent)
		:AbstractSubApp(mainApp)
	{
		refreshRate = 100;
		trainingPlanRepository = &trainingPlanRepository_;
		trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &LearningStateController::trainingPlansChanged, *this);
		window.reset(new LearningStateWindow(*this, parent));
		iterationsSinceLearningStateChanged = 0;
		trainingPlansChanged(*trainingPlanRepository);
	}

	void LearningStateController::prepareClose()
	{
		for (int i = 0; i < selectedDataSets.size(); i++)
		{
			selectedDataSets[i].trainingPlan->getLearningState().removeObserver(EVT_LS_DS_CHANGED, &LearningStateController::learningStateChanged, *this);
		}

		trainingPlanRepository->removeObserver(EVT_TP_CHANGED, &LearningStateController::trainingPlansChanged, *this);
	}

	LearningStateWindow& LearningStateController::getWindow()
	{
		return *window.get();
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& LearningStateController::getTrainingPlans() const
	{
		return trainingPlanRepository->getTrainingPlans();
	}

	void LearningStateController::trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository)
	{
		window->refreshTrainingPlans();
	}

	void LearningStateController::setSelectedTrainingPlan(int trainingPlanIndex)
	{
		selectedTrainingPlan = trainingPlanRepository->getTrainingPlans()[trainingPlanIndex].get();
	}

	AbstractTrainingPlan& LearningStateController::getSelectedTrainingPlan()
	{
		return *selectedTrainingPlan;
	}

	void LearningStateController::learningStateChanged(LearningState& learningState)
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
		return selectedTrainingPlan->getLearningState().tries;
	}

	std::string LearningStateController::addDataSet(int tryNumber, int dataSetIndex)
	{
		selectedTrainingPlan->getLearningState().registerObserver(EVT_LS_DS_CHANGED, &LearningStateController::learningStateChanged, *this);

		std::string dataSetLabel = selectedTrainingPlan->getDataSetLabels()[dataSetIndex];
		DataSetSelection newSelection;
		newSelection.trainingPlan = selectedTrainingPlan;
		newSelection.tryNumber = tryNumber;
		newSelection.label = dataSetLabel;

		selectedDataSets.push_back(newSelection);
		return dataSetLabel;
	}

	std::vector<DataSetSelection>& LearningStateController::getSelectedDataSets()
	{
		return selectedDataSets;
	}

	void LearningStateController::removeDataSet(int dataSetIndex)
	{
		bool removeObserver = true;
		for (int i = 0; i < selectedDataSets.size(); i++)
		{
			if (i != dataSetIndex && selectedDataSets[i].trainingPlan == selectedDataSets[dataSetIndex].trainingPlan)
			{
				removeObserver = false;
				break;
			}
		}
		if (removeObserver)
			selectedDataSets[dataSetIndex].trainingPlan->getLearningState().removeObserver(EVT_LS_DS_CHANGED, &LearningStateController::learningStateChanged, *this);
		selectedDataSets.erase(selectedDataSets.begin() + dataSetIndex);
	}

	const std::string& LearningStateController::getComparisonDataSetLabel() const
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
			std::vector<std::string> labels = selectedDataSets[i].trainingPlan->getDataSetLabels();
			for (auto dataSetLabel = labels.begin(); dataSetLabel != labels.end(); dataSetLabel++)
			{
				if (std::find(possibilities.begin(), possibilities.end(), *dataSetLabel) == possibilities.end())
				{
					possibilities.push_back(*dataSetLabel);
				}
			}
		}

		for (int i = 0; i < selectedDataSets.size(); i++)
		{
			std::vector<std::string> labels = selectedDataSets[i].trainingPlan->getDataSetLabels();
			for (auto possibility = possibilities.begin(); possibility != possibilities.end(); )
			{
				if (*possibility != DEFAULT_COMP_DS && std::find(labels.begin(), labels.end(), *possibility) == labels.end())
				{
					possibility = possibilities.erase(possibility);
				}
				else
					possibility++;
			}
		}

		return possibilities;
	}
}