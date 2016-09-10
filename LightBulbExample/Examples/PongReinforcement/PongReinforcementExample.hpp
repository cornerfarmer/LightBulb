
#pragma once

#ifndef _PONGREINFORCEMENTEXAMPLE_H_
#define _PONGREINFORCEMENTEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class PongReinforcementWorld;
class AbstractReinforcementWorld;
struct FeedForwardNetworkTopologyOptions;

class PongReinforcementExample : public LightBulb::AbstractLearningRuleTrainingPlan
{
private:
	PongReinforcementWorld* world;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	PongReinforcementWorld* createWorld();
public:
	PongReinforcementExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
	PongReinforcementWorld* getWorld();
};

USE_PARENT_SERIALIZATION(PongReinforcementExample, LightBulb::AbstractLearningRuleTrainingPlan);

#endif
