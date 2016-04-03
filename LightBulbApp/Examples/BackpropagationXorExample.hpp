#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLE_H_
#define _BACKPROPAGATIONXOREXAMPLE_H_


// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include <Learning/BackpropagationLearningRule.hpp>

// Library includes

// Forward declarations

// A techer manages many techingLessons
class BackpropagationXorExample : public AbstractTrainingPlan
{
	template <class Archive>
	friend void serialize(Archive& archive, BackpropagationXorExample& trainingPlan);
private:
	bool pauseRequested;
	std::unique_ptr<BackpropagationLearningRule> learningRule;
protected:
	void run(bool initial);
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
