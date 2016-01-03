#pragma once

#ifndef _ABSTRACTCOEVOLUTIONWORLD_H_
#define _ABSTRACTCOEVOLUTIONWORLD_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class AbstractCoevolutionWorld : public AbstractSimpleEvolutionWorld
{
private:
	std::unique_ptr<AbstractCombiningStrategy> combiningStrategy;
	std::map<AbstractEvolutionObject*, double> fitnessValues;
protected:
public:
	AbstractCoevolutionWorld(AbstractCombiningStrategy* combiningStrategy_);
	bool doSimulationStep(); 
	double getScore(AbstractEvolutionObject* object);
	virtual int compareObjects(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2) = 0;
	virtual int rateKI(AbstractEvolutionObject* rateKI) { return 0; };
};

#endif
