#pragma once

#ifndef _LEARNINGSTATECONTROLLER_H_
#define _LEARNINGSTATECONTROLLER_H_

// Library includes
#include <vector>
#include <map>

// Includes
#include "LearningStateWindow.hpp"
#include "AbstractSubApp.hpp"
#include "Learning/LearningState.hpp"

#define DEFAULT_COMP_DS "Iterations"

namespace LightBulb
{
	// Forward declarations
	class TrainingWindow;
	class TrainingController;
	class TrainingPlanRepository;
	class AbstractTrainingPlan;

	struct DataSetSelection
	{
		AbstractTrainingPlan* trainingPlan;
		int tryNumber;
		std::string label;

		DataSet* getDataSet(std::string otherLabel = "");
	};

	class LearningStateController : public AbstractSubApp
	{
	private:
		std::unique_ptr<LearningStateWindow> window;
		TrainingController* trainingController;
		TrainingPlanRepository* trainingPlanRepository;
		AbstractTrainingPlan* selectedTrainingPlan;
		int iterationsSinceLearningStateChanged;
		int refreshRate;
		bool refreshScheduled;
		std::vector<DataSetSelection> selectedDataSets;
		std::string comparisonDataSetLabel;

	protected:
		void prepareClose() override;
	public:
		LearningStateController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent = nullptr);
		LearningStateWindow* getWindow();
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans() const;
		void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
		void setSelectedTrainingPlan(int trainingPlanIndex);
		AbstractTrainingPlan* getSelectedTrainingPlan();
		void learningStateChanged(LearningState* learningState);
		void setRefreshRate(int newRefreshRate);
		int getRefreshRate();
		void refreshFinished();
		std::vector<std::string> getDataSetLabels();
		int getTryCount();
		std::string addDataSet(int tryNumber, int dataSetIndex);
		std::vector<DataSetSelection>* getSelectedDataSets();
		void removeDataSet(int dataSetIndex);
		const std::string& getComparisonDataSetLabel() const;
		void setComparisonDataSetLabel(std::string newComparisonDataSetLabel);
		static std::string getLabel();
		std::vector<std::string> getPossibleComparisonDatasetLabels();
	};
}

#endif
