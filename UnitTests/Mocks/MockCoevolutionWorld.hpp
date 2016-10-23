#pragma once

#ifndef _MOCKEVOLUTIONWORLD_H_
#define _MOCKEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionWorld.hpp>

class MockCoevolutionWorld : public LightBulb::AbstractCoevolutionWorld
{
public:
	MOCK_METHOD0(getHighscoreList, LightBulb::Highscore& ());
	MOCK_CONST_METHOD1(getRealScore, double (const LightBulb::AbstractEvolutionObject&));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(createNewObject, LightBulb::AbstractEvolutionObject* ());
	MOCK_METHOD0(resetWorld, void ());
	MOCK_METHOD1(addNewObject, LightBulb::AbstractEvolutionObject* (bool));
	MOCK_METHOD0(getEvolutionObjects, std::vector<LightBulb::AbstractEvolutionObject*>& ());
	MOCK_METHOD1(setEvolutionObjects, void (const std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD0(releaseAllObjects, void ());
	MOCK_METHOD1(addExistingObject, void (LightBulb::AbstractEvolutionObject*));
	MOCK_METHOD3(doCompare, int (LightBulb::AbstractEvolutionObject&, LightBulb::AbstractEvolutionObject&, int));
	MOCK_METHOD0(doSimulationStep, bool ());
	MOCK_CONST_METHOD1(getScore, double (const LightBulb::AbstractEvolutionObject&));
	MOCK_METHOD3(compareObjects, int (LightBulb::AbstractEvolutionObject&, LightBulb::AbstractEvolutionObject&, int));
	MOCK_METHOD1(rateKI, int (LightBulb::AbstractEvolutionObject&));
	MOCK_CONST_METHOD0(getCombiningStrategy, LightBulb::AbstractCombiningStrategy& ());
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(isParasiteWorld, bool ());
	MOCK_CONST_METHOD0(getRoundCount, int ());
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
};

#endif
