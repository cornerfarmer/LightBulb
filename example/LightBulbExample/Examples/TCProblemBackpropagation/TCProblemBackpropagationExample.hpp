#pragma once

#ifndef _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_
#define _TCPROBLEMBACKPROPAGATIONEXAMPLE_H_


// Includes
#include "TrainingPlans/AbstractSupervisedTrainingPlan.hpp"
#include "TCProblemTeacher.hpp"
#include "IO/UseParentSerialization.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class TCProblemBackpropagationExample : public LightBulb::AbstractSupervisedTrainingPlan
{
private:
	std::unique_ptr<TCProblemTeacher> teacher;
protected:
	LightBulb::AbstractNeuralNetwork* createNeuralNetwork() override;
	LightBulb::AbstractLearningRule* createLearningRate() override;
public:
	TCProblemBackpropagationExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(TCProblemBackpropagationExample, LightBulb::AbstractSupervisedTrainingPlan, );

#endif
