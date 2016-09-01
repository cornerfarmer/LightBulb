
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
	AbstractLearningRule* createLearningRate();
	SimpleReinforcementWorld* createWorld();
public:
	SimpleReinforcementExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	SimpleReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(SimpleReinforcementExample, AbstractLearningRuleTrainingPlan);

#endif
