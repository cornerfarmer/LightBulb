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
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	int getRequiredInputSize() const override;
	int getRequiredOutputSize() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(BackpropagationXorExample, LightBulb::AbstractSingleNNTrainingPlan, );

#endif
