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
class RBFNetworkBiggerExample : public LightBulb::AbstractSingleNNTrainingPlan
{
private:
	std::unique_ptr<LightBulb::Teacher> teacher;
protected:
	LightBulb::AbstractNeuralNetwork* createNeuralNetwork() override;
	LightBulb::AbstractLearningRule* createLearningRate() override;
public:
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	int getRequiredInputSize() override;
	int getRequiredOutputSize() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(RBFNetworkBiggerExample, LightBulb::AbstractSingleNNTrainingPlan);

#endif
