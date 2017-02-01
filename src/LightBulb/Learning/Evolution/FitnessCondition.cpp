// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/FitnessCondition.hpp"
// Library includes
#include <iomanip>

namespace LightBulb
{
	bool FitnessCondition::evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule)
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

	AbstractCloneable* FitnessCondition::clone() const
	{
		return new FitnessCondition(*this);
	}

	FitnessCondition::FitnessCondition(double scoreGoal_)
	{
		scoreGoal = scoreGoal_;
	}
}