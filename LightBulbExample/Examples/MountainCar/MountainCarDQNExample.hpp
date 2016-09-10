
#pragma once

#ifndef _MOUNTAINCARDQNEXAMPLE_H_
#define _MOUNTAINCARDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class MountainCarWorld;

class MountainCarDQNExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	MountainCarWorld* world;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	MountainCarWorld* createWorld();
public:
	MountainCarDQNExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	MountainCarWorld* getWorld();
};

USE_PARENT_SERIALIZATION(MountainCarDQNExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
