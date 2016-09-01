
#pragma once

#ifndef _SIMPLEREINFORCEMENTDQNEXAMPLE_H_
#define _SIMPLEREINFORCEMENTDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class SimpleReinforcementWorld;
class AbstractReinforcementWorld;
struct FeedForwardNetworkTopologyOptions;

class SimpleReinforcementDQNExample : public AbstractLearningRuleTrainingPlan
{
private:
	SimpleReinforcementWorld* world;
protected:
	AbstractLearningRule* createLearningRate();
	SimpleReinforcementWorld* createWorld();
public:
	SimpleReinforcementDQNExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	SimpleReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementDQNExample, AbstractLearningRuleTrainingPlan);

#endif
