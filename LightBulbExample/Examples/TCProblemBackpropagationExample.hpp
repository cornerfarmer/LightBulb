#pragma once

#ifndef _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_
#define _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_


// Includes
#include <Learning/BackpropagationLearningRule.hpp>
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include "TCProblemTeacher.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class TCProblemBackpropagationExample : public AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<TCProblemTeacher> teacher;
protected:
	AbstractNeuralNetwork* createNeuralNetwork();
	AbstractLearningRule* createLearningRate();
public:
	TCProblemBackpropagationExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(TCProblemBackpropagationExample, AbstractSingleNNTrainingPlan);

#endif
