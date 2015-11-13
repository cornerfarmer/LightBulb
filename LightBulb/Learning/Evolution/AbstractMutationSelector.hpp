#pragma once

#ifndef _ABSTRACTMUTATIONSELECTOR_H_
#define _ABSTRACTMUTATIONSELECTOR_H_

// Library includes
#include <vector>
#include <utility>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractMutationSelector
{
public:
	virtual ~AbstractMutationSelector() {};
	//
	virtual void initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int mutationCount) = 0;
	virtual AbstractEvolutionObject* nextMutation() = 0;
	virtual bool hasFinished() = 0;
};

#endif
