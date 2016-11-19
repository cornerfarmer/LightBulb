// Includes
#include "Learning/Evolution/RandomCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>

namespace LightBulb
{
	void RandomCombiningStrategy::combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		std::vector<AbstractIndividual*> randomOpponents = secondIndividuals;
		random_shuffle(randomOpponents.begin(), randomOpponents.end());

		for (auto firstPlayer = firstIndividuals.begin(); firstPlayer != firstIndividuals.end(); firstPlayer++)
		{
			for (int opponentIndex = 0; opponentIndex < amountOfCompetitionsPerIndividual && opponentIndex < randomOpponents.size(); opponentIndex++)
			{
				for (int r = 0; r < simulationWorld.getRoundCount(); r++)
				{
					int result = simulationWorld.compareIndividuals(**firstPlayer, *randomOpponents[opponentIndex], r);
					if (result != 0)
						setResult(**firstPlayer, *randomOpponents[opponentIndex], r, result > 0);
				}
			}
		}
	}

	RandomCombiningStrategy::RandomCombiningStrategy(int amountOfCompetitionsPerIndividual_)
	{
		amountOfCompetitionsPerIndividual = amountOfCompetitionsPerIndividual_;
	}

	int RandomCombiningStrategy::getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const
	{
		return amountOfCompetitionsPerIndividual * simulationWorld.getPopulationSize() * simulationWorld.getRoundCount();
	}
}