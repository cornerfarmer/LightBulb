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
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	int getRequiredInputSize() const override;
	int getRequiredOutputSize() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(TCProblemBackpropagationExample, LightBulb::AbstractSingleNNTrainingPlan, );

#endif
