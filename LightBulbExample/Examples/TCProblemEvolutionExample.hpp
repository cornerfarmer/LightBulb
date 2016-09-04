
#pragma once

#ifndef _TCPROBLEMEVOLUTIONEXAMPLE_H_
#define _TCPROBLEMEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TCProblemEvolutionExample : public AbstractEvolutionTrainingPlan
{
private:
protected:
	AbstractLearningRule* createLearningRate() override;
	AbstractEvolutionWorld* createWorld() override;
public:
	TCProblemEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TCProblemEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
