// Includes
#include "Learning/Evolution/ScoreCondition.hpp"
// Library includes
#include <iostream>
#include <iomanip>

namespace LightBulb
{
	bool ScoreCondition::evaluate(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, const AbstractEvolutionLearningRule& learningRule)
	{
		if (highscore.size() > 0)
		{
			return highscore.front().first >= scoreGoal;
		}
		else
		{
			return false;
		}
	}

	AbstractCloneable* ScoreCondition::clone() const
	{
		return new ScoreCondition(*this);
	}

	ScoreCondition::ScoreCondition(double scoreGoal_)
	{
		scoreGoal = scoreGoal_;
	}
}