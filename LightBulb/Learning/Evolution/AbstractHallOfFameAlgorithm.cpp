// Includes
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include <iostream>

void AbstractHallOfFameAlgorithm::simulateAgainstMember(AbstractEvolutionObject* object, int memberID)
{
	bool firstPlayerHasWon = currentWorld->compareObjects(object, members[memberID].get()) > 0;
	(*currentResults)[object][members[memberID].get()] = firstPlayerHasWon;
	(*currentResults)[members[memberID].get()][object] = !firstPlayerHasWon;
}

void AbstractHallOfFameAlgorithm::execute(AbstractCoevolutionWorld* world, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& prevResults)
{
	currentResults = &prevResults;
	currentWorld = world;
	evaluateObjects(*world->getEvolutionObjects());
}

void AbstractHallOfFameAlgorithm::addMember(AbstractEvolutionObject* newMember)
{
	members.push_back(std::unique_ptr<AbstractEvolutionObject>(newMember->clone(false)));
	log("Added " + std::to_string(members.size()) + ". hall of fame member", LL_LOW);
}

