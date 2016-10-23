#pragma once

#ifndef _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_
#define _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	class SharedCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		std::map<AbstractEvolutionObject*, double>* execute(const CombiningStrategyResults& results) override;
	};
}

#endif
