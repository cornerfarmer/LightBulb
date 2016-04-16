
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TicTacToe;

class TicTacToeEvolutionExample : public AbstractEvolutionTrainingPlan
{
private:
	TicTacToe* ticTacToe1;
protected:
	AbstractLearningRule* createLearningRate();
public:
	TicTacToeEvolutionExample();
	std::string getName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	std::vector<std::string> getDataSetLabels();
	TicTacToe* getTicTacToeWorld();
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
