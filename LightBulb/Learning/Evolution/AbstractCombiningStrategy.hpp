#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Library Includes
#include <vector>
#include <memory>

// Include
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

// Forward declarations
class AbstractCoevolutionWorld;
class AbstractEvolutionObject;

class AbstractCombiningStrategy
{
private:
	std::unique_ptr<std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>> results;
	int firstPlayerWins;
protected:	
	AbstractCoevolutionWorld* secondWorld;
	virtual void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects) = 0;
	void setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, bool firstPlayerHasWon);
public:
	AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_ = NULL);
	virtual std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>* execute(AbstractCoevolutionWorld* world);
	virtual void setSecondWorld(AbstractCoevolutionWorld* newSecondWorld);
	virtual std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>* getPrevResults();
	virtual int getFirstPlayerWins();
	virtual int getTotalMatches(AbstractCoevolutionWorld* simulationWorld) = 0;
};

#endif
