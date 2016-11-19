// Includes
#include "Learning/Evolution/FullHallOfFameAlgorithm.hpp"
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	void FullHallOfFameAlgorithm::evaluateIndividuals(std::vector<AbstractIndividual*>& individuals)
	{
		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			for (int memberIndex = 0; memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentWorld->getRoundCount(); r++)
				{
					simulateAgainstMember(**individual, memberIndex, r);
				}
			}
		}
	}
}