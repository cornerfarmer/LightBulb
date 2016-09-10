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
class BackpropagationXorExample : public LightBulb::AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<LightBulb::Teacher> teacher;
protected:
	LightBulb::AbstractNeuralNetwork* createNeuralNetwork() override;
	LightBulb::AbstractLearningRule* createLearningRate() override;
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
