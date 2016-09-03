
#pragma once

#ifndef _PONGDQNEXAMPLE_H_
#define _PONGDQNEXAMPLE_H_

#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"

class PongReinforcementWorld;
class AbstractReinforcementWorld;
struct FeedForwardNetworkTopologyOptions;

class PongDQNExample : public AbstractReinforcementTrainingPlan
{
private:
protected:
	AbstractLearningRule* createLearningRate();
	AbstractReinforcementWorld* createWorld();
public:
	PongDQNExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(PongDQNExample, AbstractReinforcementTrainingPlan);

#endif
