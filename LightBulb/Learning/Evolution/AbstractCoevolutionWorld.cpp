// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
//Library includes
#include <iostream>

AbstractCoevolutionWorld::AbstractCoevolutionWorld(bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
{
	isParasiteWorld = isParasiteWorld_;
	combiningStrategy.reset(combiningStrategy_);
	fitnessFunction.reset(fitnessFunction_);
	hallOfFameToAddAlgorithm.reset(hallOfFameToAddAlgorithm_);
	hallOfFameToChallengeAlgorithm.reset(hallOfFameToChallengeAlgorithm_);
}

bool AbstractCoevolutionWorld::doSimulationStep()
{
	auto results = combiningStrategy->execute(this);

	log(std::to_string(results.size() * results.begin()->second.size()), LL_HIGH);

	if (results.size() > 0)
		learningState->addData(std::string(isParasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_AVG_WINS, (double)combiningStrategy->getFirstPlayerWins() / combiningStrategy->getTotalMatches(this));

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

std::vector<std::string> AbstractCoevolutionWorld::getDataSetLabels()
{
	auto labels = AbstractEvolutionWorld::getDataSetLabels();
	labels.push_back(std::string(isParasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_AVG_WINS);
	return labels;
}
