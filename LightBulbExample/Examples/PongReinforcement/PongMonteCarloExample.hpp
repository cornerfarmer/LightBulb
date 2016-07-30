
#pragma once

#ifndef _PONGMONTECARLOEXAMPLE_H_
#define _PONGMONTECARLOEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementWorld;
class AbstractReinforcementWorld;
struct LayeredNetworkOptions;

class PongMonteCarloExample : public AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementWorld* world;
protected:
	AbstractLearningRule* createLearningRate();
	PongReinforcementWorld* createWorld();
public:
	PongMonteCarloExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	PongReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(PongMonteCarloExample, AbstractLearningRuleTrainingPlan);

#endif
