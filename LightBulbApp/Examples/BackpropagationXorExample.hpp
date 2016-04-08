#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLE_H_
#define _BACKPROPAGATIONXOREXAMPLE_H_


// Includes
#include <Learning/BackpropagationLearningRule.hpp>
#include "Teaching/Teacher.hpp"
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class BackpropagationXorExample : public AbstractLearningRuleTrainingPlan
{
	template <class Archive>
	friend void load(Archive& archive, BackpropagationXorExample& trainingPlan);
	template <class Archive>
	friend void save(Archive& archive, BackpropagationXorExample const& trainingPlan);
private:
	std::unique_ptr<Teacher> teacher;
protected:
	AbstractNeuralNetwork* createNeuralNetwork();
	AbstractLearningRule* createLearningRate();
public:
	std::string getName();
	std::string getDescription();
	std::string getLearningRateName();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
};
#endif
