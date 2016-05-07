
#pragma once

#ifndef _TEACHEDEVOLUTIONEXAMPLE_H_
#define _TEACHEDEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TeachedEvolutionExample : public AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(TeachedEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
