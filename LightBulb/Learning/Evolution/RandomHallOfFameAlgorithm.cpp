// Includes
#include "Learning/Evolution/RandomHallOfFameAlgorithm.hpp"
// Library includes
#include <algorithm>

void RandomHallOfFameAlgorithm::evaluateObjects(std::vector<AbstractEvolutionObject*>& objects)
{
	std::random_shuffle(members.begin(), members.end());

	for (auto object = objects.begin(); object != objects.end(); object++)
	{
		for (int memberIndex = 0; memberIndex < amountOfCompetitionsPerObject && memberIndex < members.size(); memberIndex++)
		{
			simulateAgainstMember(*object, memberIndex);
		}
	}
}

RandomHallOfFameAlgorithm::RandomHallOfFameAlgorithm(int amountOfCompetitionsPerObject_)
{
	amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
}