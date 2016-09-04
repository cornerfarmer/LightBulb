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
	AbstractNeuralNetwork* createNeuralNetwork() override;
	AbstractLearningRule* createLearningRate() override;
public:
	BackpropagationXorExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	int getRequiredInputSize() override;
	int getRequiredOutputSize() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(BackpropagationXorExample, AbstractSingleNNTrainingPlan);

#endif
