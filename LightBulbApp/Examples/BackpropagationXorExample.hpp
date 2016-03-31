#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLE_H_
#define _BACKPROPAGATIONXOREXAMPLE_H_


// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class BackpropagationXorExample : public AbstractTrainingPlan
{
private:
	bool shouldPause;
protected:
	void run();
	AbstractNeuralNetwork* createNeuralNetwork();
	void tryToPause();
public:
	std::string getName();
	std::string getDescription();
	std::string getLearningRateName();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
};
#endif
