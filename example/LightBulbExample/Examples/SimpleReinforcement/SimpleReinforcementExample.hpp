
#pragma once

#ifndef _SIMPLEREINFORCEMENTEXAMPLE_H_
#define _SIMPLEREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementEnvironment;

class SimpleReinforcementExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementEnvironment* environment;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	SimpleReinforcementEnvironment* createEnvironment();
public:
	SimpleReinforcementExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	SimpleReinforcementEnvironment& getEnvironment();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
