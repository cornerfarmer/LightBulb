// Includes
#include "Learning/Evolution/RandomCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>

void RandomCombiningStrategy::combine(AbstractCoevolutionWorld* world)
{
	std::vector<AbstractEvolutionObject*> randomOpponents = *world->getEvolutionObjects();
	std::random_shuffle(randomOpponents.begin(), randomOpponents.end());

	for (auto firstPlayer = world->getEvolutionObjects()->begin(); firstPlayer != world->getEvolutionObjects()->end(); firstPlayer++)
	{
		for (int opponentIndex = 0; opponentIndex < amountOfCompetitionsPerObject && opponentIndex < randomOpponents.size(); opponentIndex++)
		{
			int result = world->compareObjects(*firstPlayer, randomOpponents[opponentIndex]);
			if (result != 0)
				setResult(*firstPlayer, randomOpponents[opponentIndex], result > 0);
		}
	}
}

RandomCombiningStrategy::RandomCombiningStrategy(int amountOfCompetitionsPerObject_)
{
	amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
}

