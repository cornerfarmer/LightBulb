// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
//Library includes
#include <iostream>

AbstractCoevolutionWorld::AbstractCoevolutionWorld(AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameAlgorithm_)
{
	combiningStrategy.reset(combiningStrategy_);
	fitnessFunction.reset(fitnessFunction_);
	hallOfFameAlgorithm.reset(hallOfFameAlgorithm_);
}

bool AbstractCoevolutionWorld::doSimulationStep()
{
	auto results = combiningStrategy->execute(this);

	if (hallOfFameAlgorithm)
		hallOfFameAlgorithm->execute(this, results);

	fitnessValues = fitnessFunction->execute(results);

	AbstractEvolutionObject* bestAI = getHighscoreList()->front().second;
	rateKI(bestAI);

	if (hallOfFameAlgorithm)
		hallOfFameAlgorithm->addMember(bestAI);

	return false;
}

double AbstractCoevolutionWorld::getScore(AbstractEvolutionObject* object)
{
	return fitnessValues[object];
}
