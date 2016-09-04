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
	AbstractNeuralNetwork* createNeuralNetwork() override;
	AbstractLearningRule* createLearningRate() override;
public:
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	int getRequiredInputSize() override;
	int getRequiredOutputSize() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(RBFNetworkBiggerExample, AbstractSingleNNTrainingPlan);

#endif
