// Includes
#include "Learning/Evolution/FullHallOfFameAlgorithm.hpp"

void FullHallOfFameAlgorithm::evaluateObjects(std::vector<AbstractEvolutionObject*>& objects)
{
	for (auto object = objects.begin(); object != objects.end(); object++)
	{
		for (int memberIndex = 0; memberIndex < members.size(); memberIndex++)
		{
			simulateAgainstMember(*object, memberIndex);
		}
	}
}