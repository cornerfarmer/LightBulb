#pragma once

#ifndef _PERFECTOBJECTFOUNDCONDITION_H_
#define _PERFECTOBJECTFOUNDCONDITION_H_

// Includes
#include "Learning/Evolution/AbstractExitCondition.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCombiningStrategy;

	// A condition which matches if the best score only changes under a specified number for a chosen time
	class PerfectObjectFoundCondition : public AbstractExitCondition
	{
	private:
		// Counts how many times the difference was lower than the allowed minimum
		int counter;
		// Holds the time for how long the score must be lower than the allow minimum
		int count;
		bool perfectObjectExists(const AbstractCombiningStrategy& combiningStrategy) const;
	public:
		void setCount(int newCount);
		// Creates a new condition with the minimum difference and the allowed timesteps
		PerfectObjectFoundCondition(int count_);
		// Inherited:
		bool evaluate(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, const AbstractEvolutionLearningRule& learningRule) override;
	};
}

#endif
