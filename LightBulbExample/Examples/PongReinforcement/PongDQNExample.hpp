
#pragma once

#ifndef _PONGDQNEXAMPLE_H_
#define _PONGDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementWorld;
class AbstractReinforcementWorld;
struct LayeredNetworkOptions;

class PongDQNExample : public AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementWorld* world;
protected:
	AbstractLearningRule* createLearningRate();
	PongReinforcementWorld* createWorld();
public:
	PongDQNExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	PongReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(PongDQNExample, AbstractLearningRuleTrainingPlan);

#endif
