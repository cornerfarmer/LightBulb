// Includes
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

AbstractCombiningStrategy::AbstractCombiningStrategy(AbstractCoevolutionFitnessFunction* fitnessFunction_)
{
	fitnessFunction.reset(fitnessFunction_);
}

void AbstractCombiningStrategy::setResult(AbstractEvolutionObject* firstPlayer, AbstractEvolutionObject* secondPlayer, bool firstPlayerHasWon)
{
	results[firstPlayer][secondPlayer] = firstPlayerHasWon;
	results[secondPlayer][firstPlayer] = !firstPlayerHasWon;
}


std::map<AbstractEvolutionObject*, double> AbstractCombiningStrategy::execute(AbstractCoevolutionWorld* world)
{
	results.clear();

	combine(world);

	return fitnessFunction->execute(results);;
}

