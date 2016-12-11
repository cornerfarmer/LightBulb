#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLE_H_
#define _BACKPROPAGATIONXOREXAMPLE_H_


// Includes
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulbApp/TrainingPlans/AbstractSupervisedTrainingPlan.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class BackpropagationXorExample : public LightBulb::AbstractSupervisedTrainingPlan
{
private:
	std::unique_ptr<LightBulb::Teacher> teacher;
protected:
	LightBulb::AbstractNeuralNetwork* createNeuralNetwork() override;
	LightBulb::AbstractLearningRule* createLearningRate() override;
public:
	BackpropagationXorExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(BackpropagationXorExample, LightBulb::AbstractSupervisedTrainingPlan);

#endif
