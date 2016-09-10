
#pragma once

#ifndef _SIMPLEREINFORCEMENTEXAMPLE_H_
#define _SIMPLEREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementWorld;

class SimpleReinforcementExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementWorld* world;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	SimpleReinforcementWorld* createWorld();
public:
	SimpleReinforcementExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	SimpleReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
