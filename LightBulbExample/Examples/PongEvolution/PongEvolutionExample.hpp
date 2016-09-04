
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
	AbstractLearningRule* createLearningRate() override;
	FeedForwardNetworkTopologyOptions getNetworkOptions();
	AbstractEvolutionWorld* createWorld() override;
	AbstractEvolutionWorld* createParasiteWorld() override;
public:
	PongEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(PongEvolutionExample, AbstractCoevolutionTrainingPlan);

#endif
