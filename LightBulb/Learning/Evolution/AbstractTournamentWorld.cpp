// Includes
#include "Learning/Evolution/AbstractTournamentWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <algorithm>
#include <iostream>

AbstractTournamentWorld::AbstractTournamentWorld()
{
	currentLevel.reset(new std::vector<AbstractEvolutionObject*>());
	nextLevel.reset(new std::vector<AbstractEvolutionObject*>());
	cachedObjects.reset(new std::vector<AbstractEvolutionObject*>());
	cacheCounter = 0;
	cacheIndex = 0;
	cacheSize = 1000;
}

bool AbstractTournamentWorld::doSimulationStep()
{
	static AbstractEvolutionObject* lastBestOne = 0;
	for (auto cachedObject = cachedObjects->begin(); cachedObject != cachedObjects->end(); cachedObject++) {
		objects.push_back((*cachedObject)->clone(false));
	}
	
	fitnessValues.clear();

	for (int i = 0; i < 4; i++)
	{
		*currentLevel = objects;
		nextLevel->clear();
		currentLevelIndex = 0;

		while (currentLevel->size() != 1) {
			processLevel();
			nextLevel.swap(currentLevel);
			currentLevelIndex++;
		}

		if (currentLevel->size() > 0) {
			fitnessValues[currentLevel->front()] += currentLevelIndex;
		}
	}
	AbstractEvolutionObject* bestKI;
	for (auto fitnessValue = fitnessValues.begin(); fitnessValue != fitnessValues.end(); fitnessValue++) {
		if (fitnessValue->second > fitnessValues[bestKI])
			bestKI = fitnessValue->first;
	}
	int rating = rateKI(bestKI);
	/*if (rating < 100 && lastBestOne) {
		rateKI(lastBestOne);
		std::cout << compareObjects(bestKI, lastBestOne) << std::endl;
	}
	if (lastBestOne)
		delete(lastBestOne);*/
	lastBestOne = bestKI->clone(false);
	if (cacheCounter++ >= 10) {
		if (cachedObjects->size() > cacheIndex) {
			delete((*cachedObjects)[cacheIndex]);
			(*cachedObjects)[cacheIndex] = currentLevel->front()->clone(false);
		}
		else
			cachedObjects->push_back(currentLevel->front()->clone(false));
		cacheIndex = (cacheIndex + 1) % cacheSize;
		cacheCounter = 0;
	}
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
				fitnessValues[currentLevel->at(i)] += currentLevelIndex;
			} else {
				nextLevel->push_back(currentLevel->at(i));
				fitnessValues[currentLevel->at(i + 1)] += currentLevelIndex;
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