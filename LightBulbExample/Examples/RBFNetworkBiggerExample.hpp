#pragma once

#ifndef _RBFNETWORKBIGGEREXAMPLE_H_
#define _RBFNETWORKBIGGEREXAMPLE_H_



// Includes
#include "Teaching/Teacher.hpp"
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

// Library includes

// Forward declarations

// A techer manages many techingLessons
class RBFNetworkBiggerExample : public AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<Teacher> teacher;
protected:
	AbstractNeuralNetwork* createNeuralNetwork();
	AbstractLearningRule* createLearningRate();
public:
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(RBFNetworkBiggerExample, AbstractSingleNNTrainingPlan);

#endif
