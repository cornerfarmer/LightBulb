
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

class TicTacToe;

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
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, LightBulb::AbstractCoevolutionTrainingPlan, );

#endif
