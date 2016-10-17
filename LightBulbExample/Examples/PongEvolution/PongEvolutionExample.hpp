
#pragma once

#ifndef _PONGEVOLUTIONEXAMPLE_H_
#define _PONGEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"


class PongEvolutionExample : public LightBulb::AbstractCoevolutionTrainingPlan
{
private:
	LightBulb::AbstractHallOfFameAlgorithm* hof1;
	LightBulb::AbstractHallOfFameAlgorithm* hof2;
	LightBulb::SharedSamplingCombiningStrategy* cs1;
	LightBulb::SharedSamplingCombiningStrategy* cs2;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::FeedForwardNetworkTopologyOptions getNetworkOptions();
	LightBulb::AbstractEvolutionWorld* createWorld() override;
	LightBulb::AbstractEvolutionWorld* createParasiteWorld() override;
public:
	PongEvolutionExample();
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	LightBulb::AbstractTrainingPlan* getCopy() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(PongEvolutionExample, LightBulb::AbstractCoevolutionTrainingPlan);

#endif
