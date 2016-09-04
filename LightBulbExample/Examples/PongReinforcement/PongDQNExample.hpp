
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
	AbstractLearningRule* createLearningRate() override;
	AbstractReinforcementWorld* createWorld() override;
public:
	PongDQNExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(PongDQNExample, AbstractReinforcementTrainingPlan);

#endif
