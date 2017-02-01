// Includes
#include "LightBulb/LightBulbPrec.hpp"
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
						int result = simulationEnvironment.compareIndividuals(**firstPlayer, **secondPlayer, r);
						if (result != 0)
							setResult(**firstPlayer, **secondPlayer, r, result > 0);
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