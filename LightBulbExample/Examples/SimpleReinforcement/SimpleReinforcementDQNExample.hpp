
#pragma once

#ifndef _SIMPLEREINFORCEMENTDQNEXAMPLE_H_
#define _SIMPLEREINFORCEMENTDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementWorld;

class SimpleReinforcementDQNExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementWorld* world;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	SimpleReinforcementWorld* createWorld();
public:
	SimpleReinforcementDQNExample();
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	LightBulb::AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	SimpleReinforcementWorld& getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementDQNExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
