#pragma once

#ifndef _FUNCTIONEVOLUTIONEXAMPLE_H_
#define _FUNCTIONEVOLUTIONEXAMPLE_H_

#include <TrainingPlans/AbstractLearningRuleTrainingPlan.hpp>

class FunctionEvolutionExample : public AbstractLearningRuleTrainingPlan
{
private:
protected:
	AbstractNeuralNetwork* createNeuralNetwork();
	AbstractLearningRule* createLearningRate();
public:
	std::string getName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	int getRequiredInputSize();
	int getRequiredOutputSize();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(FunctionEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
