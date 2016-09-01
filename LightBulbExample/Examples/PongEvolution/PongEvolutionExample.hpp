
#pragma once

#ifndef _PONGEVOLUTIONEXAMPLE_H_
#define _PONGEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

struct FeedForwardNetworkTopologyOptions;
class SharedSamplingCombiningStrategy;
class AbstractHallOfFameAlgorithm;

class PongEvolutionExample : public AbstractCoevolutionTrainingPlan
{
private:
	AbstractHallOfFameAlgorithm* hof1;
	AbstractHallOfFameAlgorithm* hof2;
	SharedSamplingCombiningStrategy* cs1;
	SharedSamplingCombiningStrategy* cs2;
protected:
	AbstractLearningRule* createLearningRate();
	FeedForwardNetworkTopologyOptions getNetworkOptions();
	AbstractEvolutionWorld* createWorld();
	AbstractEvolutionWorld* createParasiteWorld();
public:
	PongEvolutionExample();
	std::string getDefaultName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(PongEvolutionExample, AbstractCoevolutionTrainingPlan);

#endif
