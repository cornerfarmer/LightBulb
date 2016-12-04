
#pragma once

#ifndef _PONGREINFORCEMENTEXAMPLE_H_
#define _PONGREINFORCEMENTEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementEnvironment;

class PongPolicyGradientExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementEnvironment* environment;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	PongReinforcementEnvironment* createEnvironment();
public:
	PongPolicyGradientExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	PongReinforcementEnvironment& getEnvironment();
};

USE_PARENT_SERIALIZATION(PongPolicyGradientExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
