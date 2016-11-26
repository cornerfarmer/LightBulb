#pragma once

#ifndef _FUNCTIONEVOLUTIONEXAMPLE_H_
#define _FUNCTIONEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class FunctionEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	FunctionEvolutionExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(FunctionEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan, );

#endif
