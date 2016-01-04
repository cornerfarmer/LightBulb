// Includes
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

void AbstractCombiningStrategy::setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, bool firstPlayerHasWon)
{
	results[firstPlayer][secondPlayer] = firstPlayerHasWon;
	results[secondPlayer][firstPlayer] = !firstPlayerHasWon;
}


std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> AbstractCombiningStrategy::execute(AbstractCoevolutionWorld* world)
{
	results.clear();

	combine(world);

	return results;
}

