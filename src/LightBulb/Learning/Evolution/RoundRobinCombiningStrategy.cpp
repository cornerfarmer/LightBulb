// Includes
#include "LightBulb/Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
//Library includes

namespace LightBulb
{
	void RoundRobinCombiningStrategy::combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		for (auto firstPlayer = firstIndividuals.begin(); firstPlayer != firstIndividuals.end(); firstPlayer++)
		{
			for (auto secondPlayer = secondIndividuals.begin(); secondPlayer != secondIndividuals.end(); secondPlayer++)
			{
				if (*firstPlayer != *secondPlayer)
				{
					for (int r = 0; r < simulationEnvironment.getRoundCount(); r++)
					{
						simulationEnvironment.compareIndividuals(**firstPlayer, **secondPlayer, r, firstPlayerHasWon);
						setResult(**firstPlayer, **secondPlayer, r, firstPlayerHasWon);
					}
				}
			}
		}
	}

	int RoundRobinCombiningStrategy::getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const
	{
		return simulationEnvironment.getPopulationSize() * simulationEnvironment.getPopulationSize() * simulationEnvironment.getRoundCount();
	}
}