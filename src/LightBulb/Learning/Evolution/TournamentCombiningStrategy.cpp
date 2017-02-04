// Includes
#include "LightBulb/Learning/Evolution/TournamentCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
//Library includes
#include <algorithm>

namespace LightBulb
{
	TournamentCombiningStrategy::TournamentCombiningStrategy(bool doShuffleBeforeTournament_)
	{
		doShuffleBeforeTournament = doShuffleBeforeTournament_;
		currentLevel.reset(new std::vector<AbstractIndividual*>());
		nextLevel.reset(new std::vector<AbstractIndividual*>());
	}

	int TournamentCombiningStrategy::getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const
	{
		throw std::logic_error("Not yet implemented.");
	}

	void TournamentCombiningStrategy::combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		// TODO: Try to make it work with two populations
		*currentLevel = firstIndividuals;
		nextLevel->clear();

		while (currentLevel->size() > 1) {
			processLevel(&simulationEnvironment);
			nextLevel.swap(currentLevel);
		}
	}


	void TournamentCombiningStrategy::processLevel(AbstractCoevolutionEnvironment* simulationEnvironment)
	{
		nextLevel->clear();
		if (doShuffleBeforeTournament)
			random_shuffle(currentLevel->begin(), currentLevel->end());

		for (int i = 0; i < currentLevel->size(); i += 2) {
			if (i < currentLevel->size() - 1) {
				int result = simulationEnvironment->compareIndividuals(*currentLevel->at(i), *currentLevel->at(i + 1), 0);
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
