#pragma once

#ifndef _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_
#define _CONSTANTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

// Forward declarations
class AbstractCoevolutionWorld;
class AbstractEvolutionObject;

class ConstantCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
{
protected:
public:
	std::map<AbstractEvolutionObject*, double> execute(std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& results);
};

#endif
