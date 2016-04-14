// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
//Library includes
#include <iostream>

AbstractCoevolutionWorld::AbstractCoevolutionWorld(AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
{
	combiningStrategy.reset(combiningStrategy_);
	fitnessFunction.reset(fitnessFunction_);
	hallOfFameToAddAlgorithm.reset(hallOfFameToAddAlgorithm_);
	hallOfFameToChallengeAlgorithm.reset(hallOfFameToChallengeAlgorithm_);
}

bool AbstractCoevolutionWorld::doSimulationStep()
{
	auto results = combiningStrategy->execute(this);

	if (hallOfFameToChallengeAlgorithm)
		hallOfFameToChallengeAlgorithm->execute(this, results);

	fitnessValues = fitnessFunction->execute(results);

	AbstractEvolutionObject* bestAI = getHighscoreList()->front().second;
	rateKI(bestAI);

	if (hallOfFameToAddAlgorithm)
		hallOfFameToAddAlgorithm->addMember(bestAI);

	return false;
}

double AbstractCoevolutionWorld::getScore(AbstractEvolutionObject* object)
{
	return fitnessValues[object];
}

void AbstractCoevolutionWorld::setLogger(AbstractLogger* logger_)
{
	AbstractLoggable::setLogger(logger_);
	if (hallOfFameToChallengeAlgorithm)
		hallOfFameToChallengeAlgorithm->setLogger(logger_);
	if (hallOfFameToAddAlgorithm)
		hallOfFameToAddAlgorithm->setLogger(logger_);
}
