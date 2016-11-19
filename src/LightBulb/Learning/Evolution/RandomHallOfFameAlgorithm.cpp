// Includes
#include "Learning/Evolution/RandomHallOfFameAlgorithm.hpp"
// Library includes
#include <algorithm>
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	void RandomHallOfFameAlgorithm::evaluateIndividuals(std::vector<AbstractIndividual*>& individuals)
	{
		random_shuffle(members.begin(), members.end());

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			for (int memberIndex = 0; memberIndex < amountOfCompetitionsPerIndividual && memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentWorld->getRoundCount(); r++)
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