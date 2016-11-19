// Includes
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionEnvironment.hpp"

namespace LightBulb
{
	AbstractCombiningStrategy::AbstractCombiningStrategy(AbstractCoevolutionEnvironment* secondEnvironment_)
	{
		results.reset(new CombiningStrategyResults());
		secondEnvironment = secondEnvironment_;
	}

	void AbstractCombiningStrategy::setResult(AbstractIndividual& firstPlayer, AbstractIndividual& secondPlayer, int round, bool firstPlayerHasWon)
	{
		(*results)[&firstPlayer][&secondPlayer][round] = firstPlayerHasWon;
		(*results)[&secondPlayer][&firstPlayer][round] = !firstPlayerHasWon;
		firstPlayerWins += firstPlayerHasWon;
	}

	CombiningStrategyResults& AbstractCombiningStrategy::execute(AbstractCoevolutionEnvironment& environment)
	{
		results.reset(new CombiningStrategyResults());
		firstPlayerWins = 0;

		combine(environment, environment.getIndividuals(), secondEnvironment ? secondEnvironment->getIndividuals() : environment.getIndividuals());

		return *results.get();
	}

	void AbstractCombiningStrategy::setSecondEnvironment(AbstractCoevolutionEnvironment& newSecondEnvironment)
	{
		secondEnvironment = &newSecondEnvironment;
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