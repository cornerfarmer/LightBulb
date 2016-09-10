
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

class TicTacToe;
class LightBulb::SharedSamplingCombiningStrategy;
struct LightBulb::FeedForwardNetworkTopologyOptions;

class TicTacToeEvolutionExample : public LightBulb::AbstractCoevolutionTrainingPlan
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
	TicTacToeEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, AbstractCoevolutionTrainingPlan);

#endif
