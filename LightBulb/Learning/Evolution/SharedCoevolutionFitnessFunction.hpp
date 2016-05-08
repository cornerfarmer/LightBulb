#pragma once

#ifndef _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_
#define _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
#include <IO/UseParentSerialization.hpp>

// Forward declarations

class SharedCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
{
protected:
public:
	std::map<AbstractEvolutionObject*, double>* execute(CombiningStrategyResults& results);
};

EMPTY_CHILD_SERIALIZATION(SharedCoevolutionFitnessFunction)

#endif
