// Includes
#include "Learning/Evolution/AbstractTournamentWorld.hpp"
//Library includes
#include <algorithm>

AbstractTournamentWorld::AbstractTournamentWorld()
{
	currentLevel.reset(new std::vector<AbstractEvolutionObject*>());
	nextLevel.reset(new std::vector<AbstractEvolutionObject*>());
}

bool AbstractTournamentWorld::doSimulationStep()
{
	*currentLevel = objects;
	nextLevel->clear();
	fitnessValues.clear();
	currentLevelIndex = 0;

	while (currentLevel->size() != 1) {
		processLevel();
		nextLevel.swap(currentLevel);
		currentLevelIndex++;
	}

	if (currentLevel->size() > 0)
		fitnessValues[currentLevel->front()] = currentLevelIndex;

	return false;
}


void AbstractTournamentWorld::processLevel()
{
	nextLevel->clear();
	std::random_shuffle(currentLevel->begin(), currentLevel->end());

	for (int i = 0; i < currentLevel->size(); i+=2) {
		if (i < currentLevel->size() - 1) {
			int result = compareObjects(currentLevel->at(i), currentLevel->at(i + 1));
			if (result == 0) {
				result = (rand() > RAND_MAX / 2 ? 1 : -1);
			}
			if (result < 0) {
				nextLevel->push_back(currentLevel->at(i + 1));
				fitnessValues[currentLevel->at(i)] = currentLevelIndex;
			} else {
				nextLevel->push_back(currentLevel->at(i));
				fitnessValues[currentLevel->at(i + 1)] = currentLevelIndex;
			}
		} else {
			nextLevel->push_back(currentLevel->at(i));
		}
	}
}

double AbstractTournamentWorld::getScore(AbstractEvolutionObject* object)
{
	return fitnessValues[object];
}