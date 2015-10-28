#pragma once

#ifndef _BESTAICOUNTCONDITION_H_
#define _BESTAICOUNTCONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

// Forward declarations
class TicTacToe;

// A condition which matches if the best score only changes under a specified number for a chosen time
class BestAICountCondition : public AbstractExitCondition
{
private:
	TicTacToe* world;
	int count;
public:
	virtual ~BestAICountCondition() {}
	//
	BestAICountCondition(TicTacToe* world_, int count_, bool enableDebugOutput_);
	// Inherited:
	bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
