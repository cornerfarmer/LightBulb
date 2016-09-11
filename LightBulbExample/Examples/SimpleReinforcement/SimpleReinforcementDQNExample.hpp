
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
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	SimpleReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementDQNExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
