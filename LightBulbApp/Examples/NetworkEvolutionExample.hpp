#pragma once

#ifndef _NETWORKEVOLUTIONEXAMPLE_H_
#define _NETWORKEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class NetworkEvolutionExample : public AbstractEvolutionTrainingPlan
{
private:
protected:
	AbstractLearningRule* createLearningRate();
public:
	std::string getName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	std::vector<std::string> getDataSetLabels();
};

USE_PARENT_SERIALIZATION(NetworkEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
