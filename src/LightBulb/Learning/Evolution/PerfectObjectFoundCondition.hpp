#pragma once

#ifndef _PERFECTOBJECTFOUNDCONDITION_H_
#define _PERFECTOBJECTFOUNDCONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCombiningStrategy;
	/**
	 * \brief A condition which matches if a perfect object exists for a chosen amount of time.
	 * \details A perfect object is a object which wins against every object in the other population.
	 */
	class PerfectObjectFoundCondition : public AbstractExitCondition
	{
	private:
		/**
		 * \brief Counts how many times a perfect object existed.
		 */
		int counter;
		/**
		 * \brief Contains the time for how long a perfect object has to exist.
		 */
		int count;
		/**
		 * \brief Returns if an perfect object exists.
		 * \param combiningStrategy The combining strategy which contains the last combining results.
		 * \return True, if an perfect object exists.
		 */
		bool perfectObjectExists(const AbstractCombiningStrategy& combiningStrategy) const;
	public:
		/**
		 * \brief Creates a new perfect object found condition.
		 * \param count_ Determines how many times a perfect object has to exist until the condition should match.
		 */
		PerfectObjectFoundCondition(int count_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
