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
		virtual std::map<AbstractEvolutionObject*, double>* execute(CombiningStrategyResults& results) = 0;
	};
}

#endif
