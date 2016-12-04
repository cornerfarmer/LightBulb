#pragma once

#ifndef _FITNESSCONDITION_H_
#define _FITNESSCONDITION_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	/**
	 * \brief A condition which matches if the best fitness exceeds a specified fitness goal.
	 */
	class FitnessCondition : public AbstractExitCondition
	{
	private:
		/**
		 * \brief The fitness which should reached.
		 */
		double scoreGoal;
	public:
		/**
		 * \brief Creates a fitness condition.
		 * \param fitnessGoal_ The fitness which should be reached.
		 */
		FitnessCondition(double fitnessGoal_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
