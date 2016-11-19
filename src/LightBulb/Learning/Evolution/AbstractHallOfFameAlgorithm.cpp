// Includes
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
#include <iostream>

namespace LightBulb
{
	void AbstractHallOfFameAlgorithm::simulateAgainstMember(AbstractIndividual& individual, int memberID, int round)
	{
		bool firstPlayerHasWon = currentEnvironment->compareIndividuals(individual, *members[memberID].get(), round) > 0;
		(*currentResults)[&individual][members[memberID].get()][round] = firstPlayerHasWon;
		(*currentResults)[members[memberID].get()][&individual][round] = !firstPlayerHasWon;
	}

	void AbstractHallOfFameAlgorithm::execute(AbstractCoevolutionEnvironment& environment, CombiningStrategyResults& prevResults)
	{
		currentResults = &prevResults;
		currentEnvironment = &environment;
		evaluateIndividuals(environment.getIndividuals());
	}

	void AbstractHallOfFameAlgorithm::addMember(AbstractIndividual* newMember)
	{
		members.push_back(std::unique_ptr<AbstractIndividual>(newMember->clone(false)));
		log("Added " + std::to_string(members.size()) + ". hall of fame member", LL_LOW);
	}
}

