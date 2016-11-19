#pragma once

#ifndef _SCORECONDITION_H_
#define _SCORECONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	/**
	 * \brief A condition which matches if the best score exceeds a specified score goal.
	 */
	class ScoreCondition : public AbstractExitCondition
	{
	private:
		/**
		 * \brief The score which should reached.
		 */
		double scoreGoal;
	public:
		/**
		 * \brief Creates a score condition.
		 * \param scoreGoal_ The score which should reached.
		 */
		ScoreCondition(double scoreGoal_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
