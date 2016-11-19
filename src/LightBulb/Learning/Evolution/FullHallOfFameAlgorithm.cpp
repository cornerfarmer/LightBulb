// Includes
#include "Learning/Evolution/FullHallOfFameAlgorithm.hpp"
#include "AbstractCoevolutionEnvironment.hpp"

namespace LightBulb
{
	void FullHallOfFameAlgorithm::evaluateIndividuals(std::vector<AbstractIndividual*>& individuals)
	{
		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			for (int memberIndex = 0; memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentEnvironment->getRoundCount(); r++)
				{
					simulateAgainstMember(**individual, memberIndex, r);
				}
			}
		}
	}
}