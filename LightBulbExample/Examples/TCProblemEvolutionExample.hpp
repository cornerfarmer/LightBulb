
#pragma once

#ifndef _TCPROBLEMEVOLUTIONEXAMPLE_H_
#define _TCPROBLEMEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TCProblemEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionWorld* createWorld() override;
public:
	TCProblemEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TCProblemEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
