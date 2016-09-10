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
class TCProblemBackpropagationExample : public LightBulb::AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<TCProblemTeacher> teacher;
protected:
	LightBulb::AbstractNeuralNetwork* createNeuralNetwork() override;
	LightBulb::AbstractLearningRule* createLearningRate() override;
public:
	TCProblemBackpropagationExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	int getRequiredInputSize() override;
	int getRequiredOutputSize() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TCProblemBackpropagationExample, AbstractSingleNNTrainingPlan);

#endif
