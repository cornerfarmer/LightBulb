// Includes
#include "Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

void RoundRobinCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
{
	for (auto firstPlayer = firstObjects->begin(); firstPlayer != firstObjects->end(); firstPlayer++)
	{
		for (auto secondPlayer = secondObjects->begin(); secondPlayer != secondObjects->end(); secondPlayer++)
		{
			if (*firstPlayer != *secondPlayer)
			{
				int result = simulationWorld->compareObjects(*firstPlayer, *secondPlayer);
				if (result != 0)
					setResult(*firstPlayer, *secondPlayer, result > 0);
			}
		}
	}
}

int RoundRobinCombiningStrategy::getTotalMatches(AbstractCoevolutionWorld* simulationWorld)
{
	return simulationWorld->getEvolutionObjects()->size() * simulationWorld->getEvolutionObjects()->size();
}
