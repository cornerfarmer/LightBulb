// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
//Library includes
#include <iostream>

namespace LightBulb
{
	AbstractCoevolutionWorld::AbstractCoevolutionWorld(bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
	{
		parasiteWorld = isParasiteWorld_;
		combiningStrategy.reset(combiningStrategy_);
		fitnessFunction.reset(fitnessFunction_);
		hallOfFameToAddAlgorithm.reset(hallOfFameToAddAlgorithm_);
		hallOfFameToChallengeAlgorithm.reset(hallOfFameToChallengeAlgorithm_);
		comparisons = 0;
	}

	bool AbstractCoevolutionWorld::doSimulationStep()
	{
		auto results = combiningStrategy->execute(this);

		if (!learningState->disabledDatasets[std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_AVG_WINS] && results->size() > 0)
			learningState->addData(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_AVG_WINS, (double)combiningStrategy->getFirstPlayerWins() / combiningStrategy->getTotalMatches(this));

		if (hallOfFameToChallengeAlgorithm)
			hallOfFameToChallengeAlgorithm->execute(this, *results);

		fitnessValues.reset(fitnessFunction->execute(*results));

		AbstractEvolutionObject* bestAI = getHighscoreList()->front().second;
		rateKI(bestAI);

		if (hallOfFameToAddAlgorithm)
			hallOfFameToAddAlgorithm->addMember(bestAI);

		if (!learningState->disabledDatasets[DATASET_COMP])
			learningState->addData(DATASET_COMP, comparisons / 1000000.0);

		return false;
	}

	double AbstractCoevolutionWorld::getScore(AbstractEvolutionObject* object)
	{
		return (*fitnessValues)[object];
	}

	int AbstractCoevolutionWorld::compareObjects(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2, int round)
	{
		comparisons++;
		return doCompare(obj1, obj2, round);
	}

	AbstractCombiningStrategy* AbstractCoevolutionWorld::getCombiningStrategy()
	{
		return combiningStrategy.get();
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
		labels.push_back(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_AVG_WINS);
		if (!parasiteWorld)
			labels.push_back(DATASET_COMP);
		return labels;
	}

	bool AbstractCoevolutionWorld::isParasiteWorld()
	{
		return parasiteWorld;
	}

	int AbstractCoevolutionWorld::getRoundCount()
	{
		return 1;
	}

	void AbstractCoevolutionWorld::setRandomGenerator(AbstractRandomGenerator* randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		combiningStrategy->setRandomGenerator(randomGenerator_);
	}
}