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

	class AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		virtual ~AbstractCoevolutionFitnessFunction() {};
		virtual std::map<const AbstractEvolutionObject*, double>* execute(const CombiningStrategyResults& results) = 0;
	};
}

#endif
