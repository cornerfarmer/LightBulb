
#pragma once

#ifndef _SIMPLEREINFORCEMENTDQNEXAMPLE_H_
#define _SIMPLEREINFORCEMENTDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementEnvironment;

class SimpleReinforcementDQNExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementEnvironment* environment;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	SimpleReinforcementEnvironment* createEnvironment();
public:
	SimpleReinforcementDQNExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	SimpleReinforcementEnvironment& getEnvironment();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementDQNExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
