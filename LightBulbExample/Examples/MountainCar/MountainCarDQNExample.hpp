
#pragma once

#ifndef _MOUNTAINCARDQNEXAMPLE_H_
#define _MOUNTAINCARDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class MountainCarWorld;
class AbstractReinforcementWorld;
struct FeedForwardNetworkTopologyOptions;

class MountainCarDQNExample : public AbstractLearningRuleTrainingPlan
{
private:
	MountainCarWorld* world;
protected:
	AbstractLearningRule* createLearningRate() override;
	MountainCarWorld* createWorld();
public:
	MountainCarDQNExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	MountainCarWorld* getWorld();
};

USE_PARENT_SERIALIZATION(MountainCarDQNExample, AbstractLearningRuleTrainingPlan);

#endif
