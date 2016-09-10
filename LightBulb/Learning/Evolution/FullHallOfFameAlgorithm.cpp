// Includes
#include "Learning/Evolution/FullHallOfFameAlgorithm.hpp"
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	void FullHallOfFameAlgorithm::evaluateObjects(std::vector<AbstractEvolutionObject*>& objects)
	{
		for (auto object = objects.begin(); object != objects.end(); object++)
		{
			for (int memberIndex = 0; memberIndex < members.size(); memberIndex++)
			{
				for (int r = 0; r < currentWorld->getRoundCount(); r++)
				{
					simulateAgainstMember(*object, memberIndex, r);
				}
			}
		}
	}
}