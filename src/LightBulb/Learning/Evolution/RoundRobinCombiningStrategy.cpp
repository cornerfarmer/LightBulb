// Includes
#include "Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

namespace LightBulb
{
	void RoundRobinCombiningStrategy::combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		for (auto firstPlayer = firstIndividuals.begin(); firstPlayer != firstIndividuals.end(); firstPlayer++)
		{
			for (auto secondPlayer = secondIndividuals.begin(); secondPlayer != secondIndividuals.end(); secondPlayer++)
			{
				if (*firstPlayer != *secondPlayer)
				{
					for (int r = 0; r < simulationWorld.getRoundCount(); r++)
					{
						int result = simulationWorld.compareIndividuals(**firstPlayer, **secondPlayer, r);
						if (result != 0)
							setResult(**firstPlayer, **secondPlayer, r, result > 0);
					}
				}
			}
		}
	}

	int RoundRobinCombiningStrategy::getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const
	{
		return simulationWorld.getPopulationSize() * simulationWorld.getPopulationSize() * simulationWorld.getRoundCount();
	}
}