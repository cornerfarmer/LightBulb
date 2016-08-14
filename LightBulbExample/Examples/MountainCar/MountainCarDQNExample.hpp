
#pragma once

#ifndef _MOUNTAINCARDQNEXAMPLE_H_
#define _MOUNTAINCARDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class MountainCarWorld;
class AbstractReinforcementWorld;
struct LayeredNetworkOptions;

class MountainCarDQNExample : public AbstractLearningRuleTrainingPlan
{
private:
	MountainCarWorld* world;
protected:
	AbstractLearningRule* createLearningRate();
	MountainCarWorld* createWorld();
public:
	MountainCarDQNExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	MountainCarWorld* getWorld();
};

USE_PARENT_SERIALIZATION(MountainCarDQNExample, AbstractLearningRuleTrainingPlan);

#endif
