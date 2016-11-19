#pragma once

#ifndef _RATEDIFFERENCECONDITION_H_
#define _RATEDIFFERENCECONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	/**
	 * \brief A condition which matches if the best score only changes within a tiny interval for a chosen time.
	 */
	class RateDifferenceCondition : public AbstractExitCondition
	{
	private:
		/**
		 * \brief Contains the best score of the last generation.
		 */
		double lastBestRate;
		/**
		 * \brief Contains the minimum allowed difference.
		 */
		double difference;
		/**
		 * \brief Counts how many times the difference was lower than the allowed minimum.
		 */
		int counter;
		/**
		 * \brief Contains the time for how long the score must be lower than the allow minimum.
		 */
		int count;
	public:
		virtual ~RateDifferenceCondition() {}
		/**
		 * \brief Creates a new rate difference condition.
		 * \param difference_ The minimum allowed difference.
		 * \param count_ The time for how long the score must be lower than the allow minimum.
		 */
		RateDifferenceCondition(double difference_, int count_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
		AbstractExitCondition* clone() const override;
	};
}

#endif
