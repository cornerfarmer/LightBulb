
#pragma once

#ifndef _TCPROBLEMEVOLUTIONEXAMPLE_H_
#define _TCPROBLEMEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TCProblemEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	TCProblemEvolutionExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(TCProblemEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan, );

#endif
