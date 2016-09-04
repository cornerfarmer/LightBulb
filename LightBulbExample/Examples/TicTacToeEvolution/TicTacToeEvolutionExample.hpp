
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

struct FeedForwardNetworkTopologyOptions;
class TicTacToe;
class SharedSamplingCombiningStrategy;
class AbstractHallOfFameAlgorithm;

class TicTacToeEvolutionExample : public AbstractCoevolutionTrainingPlan
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
	TicTacToeEvolutionExample();
	std::string getDefaultName() override;
	std::string getDescription() override;
	AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, AbstractCoevolutionTrainingPlan);

#endif
