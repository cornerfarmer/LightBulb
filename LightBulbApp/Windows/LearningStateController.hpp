#pragma once

#ifndef _LEARNINGSTATECONTROLLER_H_
#define _LEARNINGSTATECONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "LearningStateWindow.hpp"

// Forward declarations
class TrainingWindow;
class TrainingController;
class TrainingPlanRepository;
class AbstractTrainingPlan;
struct LearningState;

class LearningStateController
{
private:
	std::unique_ptr<LearningStateWindow> window;
	TrainingController* trainingController;
	TrainingPlanRepository* trainingPlanRepository;
	AbstractTrainingPlan* selectedTrainingPlan;
	int iterationsSinceLearningStateChanged;
public:
	LearningStateController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent = NULL);
	LearningStateWindow* getWindow();
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
	void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
	void setSelectedTrainingPlan(int trainingPlanIndex);
	AbstractTrainingPlan* getSelectedTrainingPlan();
	void learningStateChanged(LearningState* learningState);
	std::vector<double>* getDataSet(std::string dataSetLabel);
};

#endif
