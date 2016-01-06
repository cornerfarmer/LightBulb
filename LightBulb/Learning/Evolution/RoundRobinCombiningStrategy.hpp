#pragma once

#ifndef _ROUNDROBINCOMBININGSTRATEGY_H_
#define _ROUNDROBINCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class RoundRobinCombiningStrategy : public AbstractCombiningStrategy
{
private:
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:
};

#endif
