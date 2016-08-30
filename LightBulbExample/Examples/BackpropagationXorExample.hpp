#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLE_H_
#define _BACKPROPAGATIONXOREXAMPLE_H_


// Includes
#include "Teaching/Teacher.hpp"
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class BackpropagationXorExample : public AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<Teacher> teacher;
protected:
	AbstractNeuralNetwork* createNeuralNetwork();
	AbstractLearningRule* createLearningRate();
public:
	BackpropagationXorExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(BackpropagationXorExample, AbstractSingleNNTrainingPlan);

#endif
