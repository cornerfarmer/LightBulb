#pragma once

#ifndef _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_
#define _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations

class ConstantCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
{
protected:
public:
	std::map<AbstractEvolutionObject*, double> execute(std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& results);
};

EMPTY_CHILD_SERIALIZATION(ConstantCoevolutionFitnessFunction)

#endif
