
#pragma once

#ifndef _MOUNTAINCARDQNEXAMPLE_H_
#define _MOUNTAINCARDQNEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class MountainCarEnvironment;

class MountainCarDQNExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	MountainCarEnvironment* environment;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	MountainCarEnvironment* createEnvironment();
public:
	MountainCarDQNExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
	MountainCarEnvironment& getEnvironment();
};

USE_PARENT_SERIALIZATION(MountainCarDQNExample, LightBulb::AbstractLearningRuleTrainingPlan, );

#endif
