// Includes
#include "Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

namespace LightBulb
{
	void RoundRobinCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
	{
		for (auto firstPlayer = firstObjects->begin(); firstPlayer != firstObjects->end(); firstPlayer++)
		{
			for (auto secondPlayer = secondObjects->begin(); secondPlayer != secondObjects->end(); secondPlayer++)
			{
				if (*firstPlayer != *secondPlayer)
				{
					for (int r = 0; r < simulationWorld->getRoundCount(); r++)
					{
						int result = simulationWorld->compareObjects(**firstPlayer, **secondPlayer, r);
						if (result != 0)
							setResult(*firstPlayer, *secondPlayer, r, result > 0);
					}
				}
			}
		}
	}

	int RoundRobinCombiningStrategy::getTotalMatches(AbstractCoevolutionWorld* simulationWorld)
	{
		return simulationWorld->getPopulationSize() * simulationWorld->getPopulationSize() * simulationWorld->getRoundCount();
	}
}