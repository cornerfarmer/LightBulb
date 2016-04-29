// Includes
#include "Learning/Evolution/RandomCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>

void RandomCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
{
	std::vector<AbstractEvolutionObject*> randomOpponents = *secondObjects;
	std::random_shuffle(randomOpponents.begin(), randomOpponents.end());

	for (auto firstPlayer = firstObjects->begin(); firstPlayer != firstObjects->end(); firstPlayer++)
	{
		for (int opponentIndex = 0; opponentIndex < amountOfCompetitionsPerObject && opponentIndex < randomOpponents.size(); opponentIndex++)
		{
			int result = simulationWorld->compareObjects(*firstPlayer, randomOpponents[opponentIndex]);
			if (result != 0)
				setResult(*firstPlayer, randomOpponents[opponentIndex], result > 0);
		}
	}
}

RandomCombiningStrategy::RandomCombiningStrategy(int amountOfCompetitionsPerObject_)
{
	amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
}

int RandomCombiningStrategy::getTotalMatches(AbstractCoevolutionWorld* simulationWorld)
{
	return amountOfCompetitionsPerObject * simulationWorld->getPopulationSize();
}
