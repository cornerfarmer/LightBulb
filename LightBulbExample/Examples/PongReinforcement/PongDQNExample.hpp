
#pragma once

#ifndef _PONGDQNEXAMPLE_H_
#define _PONGDQNEXAMPLE_H_

#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"

class PongReinforcementWorld;

class PongDQNExample : public LightBulb::AbstractReinforcementTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractReinforcementWorld* createWorld() override;
public:
	PongDQNExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(PongDQNExample, LightBulb::AbstractReinforcementTrainingPlan);

#endif
