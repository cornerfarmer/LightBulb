// Includes
#include "LightBulb/Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	void AbstractHallOfFameAlgorithm::simulateAgainstMember(AbstractIndividual& individual, int memberID, int round)
	{
		currentEnvironment->compareIndividuals(individual, *members[memberID].get(), round, firstPlayerHasWon);

		currentResults->resultVector.getEigenValueForEditing()(currentResults->nextResultIndex) = firstPlayerHasWon.getEigenValue();
		currentResults->resultVector.getEigenValueForEditing()(currentResults->nextResultIndex + 1) = !firstPlayerHasWon.getEigenValue();

		currentResults->matchIndices[&individual][members[memberID].get()][round] = currentResults->nextResultIndex++;
		currentResults->matchIndices[members[memberID].get()][&individual][round] = currentResults->nextResultIndex++;
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
	
	AbstractHallOfFameAlgorithm::AbstractHallOfFameAlgorithm() = default;

	AbstractHallOfFameAlgorithm::~AbstractHallOfFameAlgorithm() = default;
}

