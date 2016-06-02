
#pragma once

#ifndef _TCPROBLEMEVOLUTIONEXAMPLE_H_
#define _TCPROBLEMEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TCProblemEvolutionExample : public AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(TCProblemEvolutionExample, AbstractLearningRuleTrainingPlan);

#endif
