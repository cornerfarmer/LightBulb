
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
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	MountainCarWorld& getWorld();
};

USE_PARENT_SERIALIZATION(MountainCarDQNExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
