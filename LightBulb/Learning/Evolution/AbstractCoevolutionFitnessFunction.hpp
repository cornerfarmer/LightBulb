#pragma once

#ifndef _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_
#define _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionWorld;
	class AbstractEvolutionObject;
	/**
	 * \brief Describes a function which calculates fitness values from CombiningStrategyResults.
	 */
	class AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		virtual ~AbstractCoevolutionFitnessFunction() {};
		/**
		 * \brief Calculate fitness values from the given CombiningStrategyResults.
		 * \param results The combining strategy results.
		 * \return A map which contains fitness values for all evolution objects.
		 */
		virtual std::map<const AbstractEvolutionObject*, double>* execute(const CombiningStrategyResults& results) = 0;
	};
}

#endif
