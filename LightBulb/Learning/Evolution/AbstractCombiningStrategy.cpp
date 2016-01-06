// Includes
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"

AbstractCombiningStrategy::AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_)
{
	secondWorld = secondWorld_;
}

void AbstractCombiningStrategy::setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, bool firstPlayerHasWon)
{
	results[firstPlayer][secondPlayer] = firstPlayerHasWon;
	results[secondPlayer][firstPlayer] = !firstPlayerHasWon;
}

std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> AbstractCombiningStrategy::execute(AbstractCoevolutionWorld* world)
{
	results.clear();

	combine(world, world->getEvolutionObjects(), secondWorld ? secondWorld->getEvolutionObjects() : world->getEvolutionObjects());

	return results;
}

void AbstractCombiningStrategy::setSecondWorld(AbstractCoevolutionWorld* newSecondWorld)
{
	secondWorld = newSecondWorld;
}

