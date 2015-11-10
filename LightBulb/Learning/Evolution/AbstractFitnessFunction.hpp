#pragma once

#ifndef _ABSTRACTFITNESSFUNCTION_H_
#define _ABSTRACTFITNESSFUNCTION_H_

// Library Includes
#include <vector>
#include <utility>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractFitnessFunction
{
public:
	virtual ~AbstractFitnessFunction() {};
	//
	virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
};

#endif
