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
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* getCopy() const override;
	int getRequiredInputSize() const override;
	int getRequiredOutputSize() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(RBFNetworkBiggerExample, LightBulb::AbstractSingleNNTrainingPlan);

#endif
