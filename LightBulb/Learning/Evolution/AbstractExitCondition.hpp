#pragma once

#ifndef _ABSTRACTEXITCONDITION_H_
#define _ABSTRACTEXITCONDITION_H_

// Includes
#include "Logging/AbstractLoggable.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionLearningRule;

	// This class describes a condition which describes if the learning process has finished.
	class AbstractExitCondition : public AbstractLoggable
	{
	protected:
	public:
		virtual ~AbstractExitCondition() {};
		// Evaluate the condition (true => stop the learning process)
		virtual bool evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, AbstractEvolutionLearningRule* learningRule) = 0;
	};
}

#endif
