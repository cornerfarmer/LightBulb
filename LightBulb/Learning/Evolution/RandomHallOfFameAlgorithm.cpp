// Includes
#include "Learning/Evolution/RandomHallOfFameAlgorithm.hpp"
// Library includes
#include <algorithm>
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	void RandomHallOfFameAlgorithm::evaluateObjects(std::vector<AbstractEvolutionObject*>& objects)
	{
		std::random_shuffle(members.begin(), members.end());

		for (auto object = objects.begin(); object != objects.end(); object++)
		{
			for (int memberIndex = 0; memberIndex < amountOfCompetitionsPerObject && memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentWorld->getRoundCount(); r++)
				{
					simulateAgainstMember(*object, memberIndex, r);
				}
			}
		}
	}

	RandomHallOfFameAlgorithm::RandomHallOfFameAlgorithm(int amountOfCompetitionsPerObject_)
	{
		amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
	}
}