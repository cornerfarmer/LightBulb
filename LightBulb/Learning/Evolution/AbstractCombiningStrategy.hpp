#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

// Forward declarations
class AbstractCoevolutionWorld;
class AbstractEvolutionObject;

class AbstractCombiningStrategy
{
private:
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> results;	
protected:	
	virtual void combine(AbstractCoevolutionWorld* world) = 0;
	void setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, bool firstPlayerHasWon);
public:
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> execute(AbstractCoevolutionWorld* world);
	
};

#endif
