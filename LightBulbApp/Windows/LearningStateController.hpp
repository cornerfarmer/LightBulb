#pragma once

#ifndef _LEARNINGSTATECONTROLLER_H_
#define _LEARNINGSTATECONTROLLER_H_

// Library includes
#include <vector>
#include <map>

// Includes
#include "LearningStateWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class TrainingWindow;
class TrainingController;
class TrainingPlanRepository;
class AbstractTrainingPlan;
struct LearningState;

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
	std::vector<std::pair<std::string, std::vector<double>*>> selectedDataSets;
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
	std::vector<std::pair<std::string, std::vector<double>*>>* getSelectedDataSets();
	void removeDataSet(int dataSetIndex);
	static std::string getLabel();
};

#endif
