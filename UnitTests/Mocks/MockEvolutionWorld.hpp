#pragma once

#ifndef _MOCKEVOLUTIONWORLD_H_
#define _MOCKEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

class MockEvolutionWorld : public LightBulb::AbstractEvolutionWorld
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD0(getEvolutionObjects, std::vector<LightBulb::AbstractEvolutionObject*>& ());
	MOCK_METHOD1(setEvolutionObjects, void (const std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD1(addNewObject, LightBulb::AbstractEvolutionObject* (bool));
	MOCK_METHOD0(doSimulationStep, bool ());
	MOCK_METHOD0(getHighscoreList, LightBulb::Highscore& ());
	MOCK_CONST_METHOD1(getScore, double (const LightBulb::AbstractEvolutionObject&));
	MOCK_CONST_METHOD1(getRealScore, double (const LightBulb::AbstractEvolutionObject&));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(releaseAllObjects, void ());
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(addExistingObject, void (LightBulb::AbstractEvolutionObject*));
};

#endif
