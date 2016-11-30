#pragma once

#ifndef _PERFECTINDIVIDUALFOUNDCONDITION_H_
#define _PERFECTINDIVIDUALFOUNDCONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCombiningStrategy;
	/**
	 * \brief A condition which matches if a perfect individual exists for a chosen amount of time.
	 * \details A perfect individual is a individual which wins against every individual in the other population.
	 */
	class PerfectIndividualFoundCondition : public AbstractExitCondition
	{
	private:
		/**
		 * \brief Counts how many times a perfect individual existed.
		 */
		int counter;
		/**
		 * \brief Contains the time for how long a perfect individual has to exist.
		 */
		int count;
		/**
		 * \brief Returns if an perfect individual exists.
		 * \param combiningStrategy The combining strategy which contains the last combining results.
		 * \return True, if an perfect individual exists.
		 */
		bool perfectIndividualExists(const AbstractCombiningStrategy& combiningStrategy) const;
	public:
		/**
		 * \brief Creates a new perfect individual found condition.
		 * \param count_ Determines how many times a perfect individual has to exist until the condition should match.
		 */
		PerfectIndividualFoundCondition(int count_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
