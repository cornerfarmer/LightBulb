#pragma once

#ifndef _EXAMPLETRAININGPLAN_H_
#define _EXAMPLETRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class ExampleTrainingPlan : public AbstractTrainingPlan
{
private:
	bool shouldPause;
protected:
	void run(bool initial);
	AbstractNeuralNetwork* createNeuralNetwork();
	void tryToPause();
public:
	std::string getName();
	std::string getDescription();
	std::string getLearningRuleName();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
	std::vector<std::string> getDataSetLabels();
	LearningState* getLearningState();
};

#endif
