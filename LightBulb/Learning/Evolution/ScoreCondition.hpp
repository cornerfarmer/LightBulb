#pragma once

#ifndef _SCORECONDITION_H_
#define _SCORECONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

// Forward declarations

class ScoreCondition : public AbstractExitCondition
{
private:
	// Holds the best score of the last generation
	double scoreGoal;
public:
	ScoreCondition(double scoreGoal_);
	// Inherited:
	bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, AbstractEvolutionLearningRule* learningRule) override;
};

#endif
