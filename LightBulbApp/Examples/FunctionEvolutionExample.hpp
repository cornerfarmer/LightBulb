#pragma once

#ifndef _FUNCTIONEVOLUTIONEXAMPLE_H_
#define _FUNCTIONEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class FunctionEvolutionExample : public AbstractEvolutionTrainingPlan
{
private:
protected:
	AbstractLearningRule* createLearningRate();
	AbstractEvolutionWorld* createWorld();
public:
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(FunctionEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
