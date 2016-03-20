#pragma once

#ifndef _TOURNAMENTCOMBININGSTRATEGY_H_
#define _TOURNAMENTCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>
#include <memory>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

// Forward declarations

class TournamentCombiningStrategy : public AbstractCombiningStrategy
{
private:
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> cachedObjects;
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> currentLevel;
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> nextLevel;
	void processLevel(AbstractCoevolutionWorld* world);
	void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects);
public:	
	TournamentCombiningStrategy();	
};

#endif
