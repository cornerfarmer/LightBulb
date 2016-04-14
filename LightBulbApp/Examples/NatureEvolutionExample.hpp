#pragma once

#ifndef _EVOLUTIONEXAMPLE_H_
#define _EVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class NatureEvolutionExample : public AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(NatureEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
