// Includes
#include "Learning/Evolution/TournamentCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

TournamentCombiningStrategy::TournamentCombiningStrategy()
{
	currentLevel.reset(new std::vector<AbstractEvolutionObject*>());
	nextLevel.reset(new std::vector<AbstractEvolutionObject*>());
	cachedObjects.reset(new std::vector<AbstractEvolutionObject*>());
}

void TournamentCombiningStrategy::combine(AbstractCoevolutionWorld* world)
{
	for (int i = 0; i < 4; i++)
	{
		*currentLevel = *world->getEvolutionObjects();
		nextLevel->clear();

		while (currentLevel->size() != 1) {
			processLevel(world);
			nextLevel.swap(currentLevel);
		}
	}
}


void TournamentCombiningStrategy::processLevel(AbstractCoevolutionWorld* world)
{
	nextLevel->clear();
	std::random_shuffle(currentLevel->begin(), currentLevel->end());

	for (int i = 0; i < currentLevel->size(); i+=2) {
		if (i < currentLevel->size() - 1) {
			int result = world->compareObjects(currentLevel->at(i), currentLevel->at(i + 1));
			if (result == 0) {
				result = (rand() > RAND_MAX / 2 ? 1 : -1);
			}
			setResult(currentLevel->at(i), currentLevel->at(i + 1), result >= 0);

			if (result < 0) {
				nextLevel->push_back(currentLevel->at(i + 1));
			} else {
				nextLevel->push_back(currentLevel->at(i));
			}
		} else {
			nextLevel->push_back(currentLevel->at(i));
		}
	}
}

