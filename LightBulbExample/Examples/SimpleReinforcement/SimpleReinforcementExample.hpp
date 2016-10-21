
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
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	LightBulb::AbstractTrainingPlan* getCopy() const override;
	std::string getLearningRuleName() const override;
	SimpleReinforcementWorld& getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
