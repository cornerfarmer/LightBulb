#pragma once

#ifndef _SHAREDSAMPLINGCOMBININGSTRATEGY_H_
#define _SHAREDSAMPLINGCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include <IO/UseParentSerialization.hpp>

// Forward declarations

class SharedSamplingCombiningStrategy : public AbstractCombiningStrategy
{
	template <class Archive>
	friend void serialize(Archive& archive, SharedSamplingCombiningStrategy& sharedSamplingCombiningStrategy);
private:
	int amountOfCompetitionsPerObject;
	AbstractCombiningStrategy* otherCombiningStrategy;
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:
	void setSecondWorld(AbstractCoevolutionWorld* newSecondWorld);
	SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_ = 0, AbstractCoevolutionWorld* secondWorld_ = NULL);
	int getTotalMatches(AbstractCoevolutionWorld* simulationWorld);
};

#include "IO/SharedSamplingCombiningStrategyIO.hpp"

#endif
