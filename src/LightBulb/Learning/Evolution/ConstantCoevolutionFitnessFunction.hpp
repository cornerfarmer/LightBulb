#pragma once

#ifndef _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_
#define _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Calculates the fitness values by simply sum up all victories of an object.
	 */
	class ConstantCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		// Inherited:
		std::map<const AbstractEvolutionObject*, double>* execute(const CombiningStrategyResults& results) override;
	};
}

#endif
