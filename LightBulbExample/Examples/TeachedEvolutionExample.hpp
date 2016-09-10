
#pragma once

#ifndef _TEACHEDEVOLUTIONEXAMPLE_H_
#define _TEACHEDEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TeachedEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
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

USE_PARENT_SERIALIZATION(TeachedEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan);

#endif
