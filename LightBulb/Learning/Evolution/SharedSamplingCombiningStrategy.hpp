#pragma once

#ifndef _SHAREDSAMPLINGCOMBININGSTRATEGY_H_
#define _SHAREDSAMPLINGCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class SharedSamplingCombiningStrategy : public AbstractCombiningStrategy
{
private:
	int amountOfCompetitionsPerObject;
	SharedSamplingCombiningStrategy* otherCombiningStrategy;
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:
	SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_, SharedSamplingCombiningStrategy* otherCombiningStrategy_ = NULL);
	void setOtherCombiningStrategy(SharedSamplingCombiningStrategy* otherCombiningStrategy_);
	int getTotalMatches(AbstractCoevolutionWorld* simulationWorld);
};

#endif
