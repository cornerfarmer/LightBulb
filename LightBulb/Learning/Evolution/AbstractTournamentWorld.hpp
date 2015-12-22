#pragma once

#ifndef _ABSTRACTTOURNAMENTWORLD_H_
#define _ABSTRACTTOURNAMENTWORLD_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"

// Forward declarations

class AbstractTournamentWorld : public AbstractSimpleEvolutionWorld
{
private:	
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> currentLevel;
	std::unique_ptr<std::vector<AbstractEvolutionObject*>> nextLevel;
	std::map<AbstractEvolutionObject*, int> fitnessValues;
	int currentLevelIndex;
	void processLevel();	
protected:
	virtual int compareObjects(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2) = 0;
public:	
	AbstractTournamentWorld();
	bool doSimulationStep(); 
	double getScore(AbstractEvolutionObject* object);
};

#endif
