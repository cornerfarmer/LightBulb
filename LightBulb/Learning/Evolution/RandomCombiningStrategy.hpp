#pragma once

#ifndef _RANDOMCOMBININGSTRATEGY_H_
#define _RANDOMCOMBININGSTRATEGY_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class RandomCombiningStrategy : public AbstractCombiningStrategy
{
private:
	int amountOfCompetitionsPerObject;
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:
	RandomCombiningStrategy(int amountOfCompetitionsPerObject_);
};

#endif
