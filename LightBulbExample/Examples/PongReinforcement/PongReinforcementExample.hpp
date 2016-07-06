
#pragma once

#ifndef _PONGREINFORCEMENTEXAMPLE_H_
#define _PONGREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementWorld;
class AbstractReinforcementWorld;
struct LayeredNetworkOptions;

class PongReinforcementExample : public AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementWorld* world;
protected:
	AbstractLearningRule* createLearningRate();
	PongReinforcementWorld* createWorld();
public:
	PongReinforcementExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	PongReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(PongReinforcementExample, AbstractLearningRuleTrainingPlan);

#endif
