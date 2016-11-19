// Includes
#include "Learning/Evolution/TournamentCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

namespace LightBulb
{
	TournamentCombiningStrategy::TournamentCombiningStrategy(bool doShuffleBeforeTournament_)
	{
		doShuffleBeforeTournament = doShuffleBeforeTournament_;
		currentLevel.reset(new std::vector<AbstractIndividual*>());
		nextLevel.reset(new std::vector<AbstractIndividual*>());
	}

	int TournamentCombiningStrategy::getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const
	{
		throw std::logic_error("Not yet implemented.");
	}

	void TournamentCombiningStrategy::combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		// TODO: Try to make it work with two populations
		*currentLevel = firstIndividuals;
		nextLevel->clear();

		while (currentLevel->size() > 1) {
			processLevel(&simulationWorld);
			nextLevel.swap(currentLevel);
		}
	}


	void TournamentCombiningStrategy::processLevel(AbstractCoevolutionWorld* simulationWorld)
	{
		nextLevel->clear();
		if (doShuffleBeforeTournament)
			random_shuffle(currentLevel->begin(), currentLevel->end());

		for (int i = 0; i < currentLevel->size(); i += 2) {
			if (i < currentLevel->size() - 1) {
				int result = simulationWorld->compareIndividuals(*currentLevel->at(i), *currentLevel->at(i + 1), 0);
				if (result == 0) {
					result = (randomGenerator->randDouble() > 0.5 ? 1 : -1);
				}
				//			setResult(currentLevel->at(i), currentLevel->at(i + 1), result >= 0);

				if (result < 0) {
					nextLevel->push_back(currentLevel->at(i + 1));
				}
				else {
					nextLevel->push_back(currentLevel->at(i));
				}
			}
			else {
				nextLevel->push_back(currentLevel->at(i));
			}
		}
	}

}