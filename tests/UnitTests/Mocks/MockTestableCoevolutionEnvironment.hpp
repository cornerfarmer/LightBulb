#pragma once

#ifndef _MOCKTESTABLECOEVOLUTIONENVIRONMENT_H_
#define _MOCKTESTABLECOEVOLUTIONENVIRONMENT_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp>

class MockTestableCoevolutionEnvironment : public LightBulb::AbstractCoevolutionEnvironment
{
public:
	MockTestableCoevolutionEnvironment(bool isParasiteEnvironment_, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_, std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_)
		: AbstractCoevolutionEnvironment(isParasiteEnvironment_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
	{
	}
	MOCK_METHOD0(getHighscoreList, LightBulb::Highscore& ());
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(createNewIndividual, LightBulb::AbstractIndividual* ());
	MOCK_METHOD0(resetEnvironment, void ());
	MOCK_METHOD1(addNewIndividual, LightBulb::AbstractIndividual* (bool));
	MOCK_METHOD0(getIndividuals, std::vector<LightBulb::AbstractIndividual*>& ());
	MOCK_METHOD1(setIndividuals, void (const std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(addExistingIndividual, void (LightBulb::AbstractIndividual*));
	MOCK_METHOD3(doCompare, int (LightBulb::AbstractIndividual&, LightBulb::AbstractIndividual&, int));

	MOCK_CONST_METHOD1(getScore, double (const LightBulb::AbstractIndividual&));
	MOCK_METHOD3(compareIndividuals, int (LightBulb::AbstractIndividual&, LightBulb::AbstractIndividual&, int));
	MOCK_METHOD1(rateIndividual, int (LightBulb::AbstractIndividual&));
	MOCK_CONST_METHOD0(getCombiningStrategy, LightBulb::AbstractCombiningStrategy& ());
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(isParasiteEnvironment, bool ());
	MOCK_CONST_METHOD0(getRoundCount, int ());
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
};

#endif
