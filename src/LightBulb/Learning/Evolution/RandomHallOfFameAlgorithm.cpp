// Includes
#include "LightBulb/Learning/Evolution/RandomHallOfFameAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
// Library includes
#include <algorithm>

namespace LightBulb
{
	void RandomHallOfFameAlgorithm::evaluateIndividuals(std::vector<AbstractIndividual*>& individuals)
	{
		random_shuffle(members.begin(), members.end());

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			for (int memberIndex = 0; memberIndex < amountOfCompetitionsPerIndividual && memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentEnvironment->getRoundCount(); r++)
				{
					simulateAgainstMember(**individual, memberIndex, r);
				}
			}
		}
	}

	RandomHallOfFameAlgorithm::RandomHallOfFameAlgorithm(int amountOfCompetitionsPerIndividual_)
	{
		amountOfCompetitionsPerIndividual = amountOfCompetitionsPerIndividual_;
	}
}
