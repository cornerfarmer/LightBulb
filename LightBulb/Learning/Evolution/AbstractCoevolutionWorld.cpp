// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
//Library includes
#include <iostream>

AbstractCoevolutionWorld::AbstractCoevolutionWorld(AbstractCombiningStrategy* combiningStrategy_)
{
	combiningStrategy.reset(combiningStrategy_);
}

bool AbstractCoevolutionWorld::doSimulationStep()
{
	fitnessValues = combiningStrategy->execute(this);
	rateKI(getHighscoreList()->front().second);
	return false;
}

double AbstractCoevolutionWorld::getScore(AbstractEvolutionObject* object)
{
	return fitnessValues[object];
}
