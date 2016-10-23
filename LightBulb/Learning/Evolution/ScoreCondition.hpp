#pragma once

#ifndef _SCORECONDITION_H_
#define _SCORECONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	// Forward declarations

	class ScoreCondition : public AbstractExitCondition
	{
	private:
		// Holds the best score of the last generation
		double scoreGoal;
	public:
		ScoreCondition(double scoreGoal_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
	};
}

#endif
