
#pragma once

#ifndef _SIMPLEREINFORCEMENTEXAMPLE_H_
#define _SIMPLEREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementWorld;
class AbstractReinforcementWorld;
struct FeedForwardNetworkTopologyOptions;

class SimpleReinforcementExample : public AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementWorld* world;
protected:
	AbstractLearningRule* createLearningRate() override;
	SimpleReinforcementWorld* createWorld();
public:
	SimpleReinforcementExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	SimpleReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementExample, AbstractLearningRuleTrainingPlan);

#endif
