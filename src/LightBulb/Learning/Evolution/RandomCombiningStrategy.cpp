// Includes
#include "Learning/Evolution/RandomCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
//Library includes
#include <algorithm>

namespace LightBulb
{
	void RandomCombiningStrategy::combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		std::vector<AbstractIndividual*> randomOpponents = secondIndividuals;
		random_shuffle(randomOpponents.begin(), randomOpponents.end());

		for (auto firstPlayer = firstIndividuals.begin(); firstPlayer != firstIndividuals.end(); firstPlayer++)
		{
			for (int opponentIndex = 0; opponentIndex < amountOfCompetitionsPerIndividual && opponentIndex < randomOpponents.size(); opponentIndex++)
			{
				for (int r = 0; r < simulationEnvironment.getRoundCount(); r++)
				{
					int result = simulationEnvironment.compareIndividuals(**firstPlayer, *randomOpponents[opponentIndex], r);
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

	int RandomCombiningStrategy::getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const
	{
		return amountOfCompetitionsPerIndividual * simulationEnvironment.getPopulationSize() * simulationEnvironment.getRoundCount();
	}
}