#pragma once

#ifndef _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_
#define _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes
#include <map>

// Include

// Forward declarations
class AbstractCoevolutionWorld;
class AbstractEvolutionObject;

class AbstractCoevolutionFitnessFunction
{
protected:
public:
	virtual std::map<AbstractEvolutionObject*, double> execute(std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& results) = 0;
};

#endif
