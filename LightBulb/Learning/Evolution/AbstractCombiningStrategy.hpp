#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Library Includes
#include <vector>
#include <memory>
#include <map>

// Include

// Forward declarations
class AbstractCoevolutionWorld;
class AbstractEvolutionObject;

typedef std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, std::map<int, bool>>> CombiningStrategyResults;

class AbstractCombiningStrategy
{
private:
	std::unique_ptr<CombiningStrategyResults> results;
	int firstPlayerWins;
protected:	
	AbstractCoevolutionWorld* secondWorld;
	virtual void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects) = 0;
	void setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, int round, bool firstPlayerHasWon);
public:
	AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_ = NULL);
	virtual CombiningStrategyResults* execute(AbstractCoevolutionWorld* world);
	virtual void setSecondWorld(AbstractCoevolutionWorld* newSecondWorld);
	virtual CombiningStrategyResults* getPrevResults();
	virtual int getFirstPlayerWins();
	virtual int getTotalMatches(AbstractCoevolutionWorld* simulationWorld) = 0;
};

#endif
