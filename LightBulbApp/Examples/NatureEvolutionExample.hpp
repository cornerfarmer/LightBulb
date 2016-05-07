#pragma once

#ifndef _EVOLUTIONEXAMPLE_H_
#define _EVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class NatureEvolutionExample : public AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(NatureEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
