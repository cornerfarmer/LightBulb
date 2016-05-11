#pragma once

#ifndef _LEARNINGSTATECONTROLLER_H_
#define _LEARNINGSTATECONTROLLER_H_

// Library includes
#include <vector>
#include <map>

// Includes
#include "LearningStateWindow.hpp"
#include "AbstractSubApp.hpp"
#include <Learning/DeltaLearningRule.hpp>

#define DEFAULT_COMP_DS "Iterations"

// Forward declarations
class TrainingWindow;
class TrainingController;
class TrainingPlanRepository;
class AbstractTrainingPlan;

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
	std::vector<std::pair<DataSetsPerTry*, std::string>> selectedDataSets;
	std::string comparisonDataSetLabel;
public:
	LearningStateController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent = NULL);
	LearningStateWindow* getWindow();
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
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
	std::vector<std::pair<DataSetsPerTry*, std::string>>* getSelectedDataSets();
	void removeDataSet(int dataSetIndex);
	std::string getComparisonDataSetLabel();
	void setComparisonDataSetLabel(std::string newComparisonDataSetLabel);
	static std::string getLabel();
	std::vector<std::string> getPossibleComparisonDatasetLabels();
};

#endif
