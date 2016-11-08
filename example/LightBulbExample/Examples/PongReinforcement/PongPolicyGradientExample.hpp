
#pragma once

#ifndef _PONGREINFORCEMENTEXAMPLE_H_
#define _PONGREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementWorld;

class PongPolicyGradientExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementWorld* world;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	PongReinforcementWorld* createWorld();
public:
	PongPolicyGradientExample();
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	PongReinforcementWorld& getWorld();
};

USE_PARENT_SERIALIZATION(PongPolicyGradientExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
