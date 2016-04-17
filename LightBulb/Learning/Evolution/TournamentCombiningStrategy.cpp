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

int TournamentCombiningStrategy::getTotalMatches(AbstractCoevolutionWorld* simulationWorld)
{
	throw std::logic_error("Not yet implemented.");
}

void TournamentCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
{
	for (int i = 0; i < 4; i++)
	{
		// TODO: Try to make it work with two populations
		*currentLevel = *firstObjects;
		nextLevel->clear();

		while (currentLevel->size() != 1) {
			processLevel(simulationWorld);
			nextLevel.swap(currentLevel);
		}
	}
}


void TournamentCombiningStrategy::processLevel(AbstractCoevolutionWorld* simulationWorld)
{
	nextLevel->clear();
	std::random_shuffle(currentLevel->begin(), currentLevel->end());

	for (int i = 0; i < currentLevel->size(); i+=2) {
		if (i < currentLevel->size() - 1) {
			int result = simulationWorld->compareObjects(currentLevel->at(i), currentLevel->at(i + 1));
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

