// Includes
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include <iostream>

namespace LightBulb
{
	void AbstractHallOfFameAlgorithm::simulateAgainstMember(AbstractEvolutionObject& object, int memberID, int round)
	{
		bool firstPlayerHasWon = currentWorld->compareObjects(object, *members[memberID].get(), round) > 0;
		(*currentResults)[&object][members[memberID].get()][round] = firstPlayerHasWon;
		(*currentResults)[members[memberID].get()][&object][round] = !firstPlayerHasWon;
	}

	void AbstractHallOfFameAlgorithm::execute(AbstractCoevolutionWorld& world, CombiningStrategyResults& prevResults)
	{
		currentResults = &prevResults;
		currentWorld = &world;
		evaluateObjects(world.getEvolutionObjects());
	}

	void AbstractHallOfFameAlgorithm::addMember(AbstractEvolutionObject* newMember)
	{
		members.push_back(std::unique_ptr<AbstractEvolutionObject>(newMember->clone(false)));
		log("Added " + std::to_string(members.size()) + ". hall of fame member", LL_LOW);
	}
}

