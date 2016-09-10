#pragma once

#ifndef _FUNCTIONEVOLUTIONEXAMPLE_H_
#define _FUNCTIONEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class FunctionEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionWorld* createWorld() override;
public:
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(FunctionEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan);

#endif
