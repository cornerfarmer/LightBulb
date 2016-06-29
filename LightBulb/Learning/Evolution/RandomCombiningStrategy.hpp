#pragma once

#ifndef _RANDOMCOMBININGSTRATEGY_H_
#define _RANDOMCOMBININGSTRATEGY_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class RandomCombiningStrategy : public AbstractCombiningStrategy
{
	template <class Archive>
	friend void serialize(Archive& archive, RandomCombiningStrategy& randomCombiningStrategy);
private:
	int amountOfCompetitionsPerObject;
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:
	RandomCombiningStrategy(int amountOfCompetitionsPerObject_ = 0);
	int getTotalMatches(AbstractCoevolutionWorld* simulationWorld);
};

#endif
