#pragma once

#ifndef _MOCKEVOLUTIONENVIRONMENT_H_
#define _MOCKEVOLUTIONENVIRONMENT_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionEnvironment.hpp>

class MockCoevolutionEnvironment : public LightBulb::AbstractCoevolutionEnvironment
{
public:
	MOCK_METHOD0(getHighscoreList, LightBulb::Highscore& ());
	MOCK_CONST_METHOD1(getRealScore, double (const LightBulb::AbstractIndividual&));
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
	MOCK_METHOD0(doSimulationStep, bool ());
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
