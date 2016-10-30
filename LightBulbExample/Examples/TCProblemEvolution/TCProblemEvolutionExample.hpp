
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
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	LightBulb::AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(TCProblemEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
