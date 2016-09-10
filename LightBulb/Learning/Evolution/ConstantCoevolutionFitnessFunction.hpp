#pragma once

#ifndef _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_
#define _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	class ConstantCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		std::map<AbstractEvolutionObject*, double>* execute(CombiningStrategyResults& results) override;
	};
}

#endif
