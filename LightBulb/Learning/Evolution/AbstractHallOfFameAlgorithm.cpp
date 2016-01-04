// Includes
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include <iostream>

void AbstractHallOfFameAlgorithm::simulateAgainstMember(AbstractEvolutionObject* object, int memberID)
{
	bool firstPlayerHasWon = currentWorld->compareObjects(object, members[memberID]) > 0;
	(*currentResults)[object][members[memberID]] = firstPlayerHasWon;
	(*currentResults)[members[memberID]][object] = !firstPlayerHasWon;
}

void AbstractHallOfFameAlgorithm::execute(AbstractCoevolutionWorld* world, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& prevResults)
{
	currentResults = &prevResults;
	currentWorld = world;
	evaluateObjects(*world->getEvolutionObjects());
}

void AbstractHallOfFameAlgorithm::addMember(AbstractEvolutionObject* newMember)
{
	members.push_back(newMember->clone(false));
	std::cout << "Added " << members.size() << ". hall of fame member" << std::endl;
}

