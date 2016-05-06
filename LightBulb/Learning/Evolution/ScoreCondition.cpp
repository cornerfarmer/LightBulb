// Includes
#include "Learning/Evolution/ScoreCondition.hpp"
// Library includes
#include <iostream>
#include <iomanip>

bool ScoreCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, AbstractEvolutionLearningRule* learningRule)
{
	if (highscore->size() > 0)
	{
		return highscore->front().first >= scoreGoal;
	}
	else
	{
		return false;
	}
}

ScoreCondition::ScoreCondition(double scoreGoal_)
{
	scoreGoal = scoreGoal_;
}
