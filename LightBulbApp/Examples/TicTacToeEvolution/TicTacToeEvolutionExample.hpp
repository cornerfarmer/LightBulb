
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

class TicTacToeEvolutionExample : public AbstractEvolutionTrainingPlan
{
private:
protected:
	AbstractLearningRule* createLearningRate();
public:
	TicTacToeEvolutionExample();
	std::string getName();
	std::string getDescription();
	AbstractTrainingPlan* getCopy();
	std::string getLearningRuleName();
	std::vector<std::string> getDataSetLabels();
};

USE_PARENT_SERIALIZATION(TicTacToeEvolutionExample, AbstractEvolutionTrainingPlan);

#endif
