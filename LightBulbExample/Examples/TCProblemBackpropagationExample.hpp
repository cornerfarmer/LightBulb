#pragma once

#ifndef _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_
#define _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_


// Includes
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include "TCProblemTeacher.hpp"
#include "IO/UseParentSerialization.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class TCProblemBackpropagationExample : public AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<TCProblemTeacher> teacher;
protected:
	AbstractNeuralNetwork* createNeuralNetwork() override;
	AbstractLearningRule* createLearningRate() override;
public:
	TCProblemBackpropagationExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	int getRequiredInputSize() override;
	int getRequiredOutputSize() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TCProblemBackpropagationExample, AbstractSingleNNTrainingPlan);

#endif
