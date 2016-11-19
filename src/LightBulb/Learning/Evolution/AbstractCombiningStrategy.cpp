// Includes
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	AbstractCombiningStrategy::AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_)
	{
		results.reset(new CombiningStrategyResults());
		secondWorld = secondWorld_;
	}

	void AbstractCombiningStrategy::setResult(AbstractIndividual& firstPlayer, AbstractIndividual& secondPlayer, int round, bool firstPlayerHasWon)
	{
		(*results)[&firstPlayer][&secondPlayer][round] = firstPlayerHasWon;
		(*results)[&secondPlayer][&firstPlayer][round] = !firstPlayerHasWon;
		firstPlayerWins += firstPlayerHasWon;
	}

	CombiningStrategyResults& AbstractCombiningStrategy::execute(AbstractCoevolutionWorld& world)
	{
		results.reset(new CombiningStrategyResults());
		firstPlayerWins = 0;

		combine(world, world.getIndividuals(), secondWorld ? secondWorld->getIndividuals() : world.getIndividuals());

		return *results.get();
	}

	void AbstractCombiningStrategy::setSecondWorld(AbstractCoevolutionWorld& newSecondWorld)
	{
		secondWorld = &newSecondWorld;
	}

	const CombiningStrategyResults& AbstractCombiningStrategy::getPrevResults() const
	{
		return *results.get();
	}

	int AbstractCombiningStrategy::getFirstPlayerWins() const
	{
		return firstPlayerWins;
	}
}