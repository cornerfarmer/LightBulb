#pragma once

#ifndef _ABSTRACTEXITCONDITION_H_
#define _ABSTRACTEXITCONDITION_H_

// Includes
#include "LightBulb/Logging/AbstractLoggable.hpp"
#include "LightBulb/Tools/AbstractCloneable.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class AbstractEvolutionLearningRule;
	/**
	 * \brief A condition which determines if the learning process has finished.
	 */
	class AbstractExitCondition : public virtual AbstractCloneable, public AbstractLoggable
	{
	protected:
	public:
		virtual ~AbstractExitCondition() {};
		/**
		 * \brief Evaluate the condition.
		 * \param highscore The current highscore.
		 * \param learningRule The learning rule.
		 * \return True, if the learning process should stop.
		 */
		virtual bool evaluate(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, const AbstractEvolutionLearningRule& learningRule) = 0;
	};
}

#endif
