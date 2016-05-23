#pragma once

#ifndef _NETWORKEVOLUTIONEXAMPLE_H_
#define _NETWORKEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

class NetworkEvolutionExample : public AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(NetworkEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
