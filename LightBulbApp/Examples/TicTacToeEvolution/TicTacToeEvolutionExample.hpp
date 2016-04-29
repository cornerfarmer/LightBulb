
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

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
	AbstractLearningRule* createLearningRate();
	AbstractEvolutionWorld* createWorld();
	AbstractEvolutionWorld* createParasiteWorld();
public:
	TicTacToeEvolutionExample();
	std::string getName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, AbstractCoevolutionTrainingPlan);

#endif
