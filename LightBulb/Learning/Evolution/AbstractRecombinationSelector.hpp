#pragma once

#ifndef _ABSTRACTRECOMBINATIONSELECTOR_H_
#define _ABSTRACTRECOMBINATIONSELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <array>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractRecombinationSelector
{
public:
	virtual ~AbstractRecombinationSelector() {};
	//
	virtual void initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount) = 0;
	virtual std::array<AbstractEvolutionObject*, 2> nextRecombination() = 0;
	virtual bool hasFinished() = 0;
};

#endif
