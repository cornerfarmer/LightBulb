
#pragma once

#ifndef _PONGEVOLUTIONEXAMPLE_H_
#define _PONGEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

struct LightBulb::FeedForwardNetworkTopologyOptions;
class SharedSamplingCombiningStrategy;
class LightBulb::AbstractHallOfFameAlgorithm;

class PongEvolutionExample : public LightBulb::AbstractCoevolutionTrainingPlan
{
private:
	LightBulb::AbstractHallOfFameAlgorithm* hof1;
	LightBulb::AbstractHallOfFameAlgorithm* hof2;
	SharedSamplingCombiningStrategy* cs1;
	SharedSamplingCombiningStrategy* cs2;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::FeedForwardNetworkTopologyOptions getNetworkOptions();
	LightBulb::AbstractEvolutionWorld* createWorld() override;
	LightBulb::AbstractEvolutionWorld* createParasiteWorld() override;
public:
	PongEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(PongEvolutionExample, LightBulb::AbstractCoevolutionTrainingPlan);

#endif
