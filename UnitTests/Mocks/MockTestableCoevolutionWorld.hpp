#pragma once

#ifndef _MOCKTESTABLECOEVOLUTIONWORLD_H_
#define _MOCKTESTABLECOEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionWorld.hpp>

class MockTestableCoevolutionWorld : public LightBulb::AbstractCoevolutionWorld
{
public:
	MockTestableCoevolutionWorld(bool isParasiteWorld_, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
		: AbstractCoevolutionWorld(isParasiteWorld_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
	{
	}
	MOCK_METHOD0(getHighscoreList, std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>* ());
	MOCK_METHOD1(getRealScore, double(LightBulb::AbstractEvolutionObject*));
	MOCK_METHOD0(initializeForLearning, void());
	MOCK_METHOD0(createNewObject, LightBulb::AbstractEvolutionObject* ());
	MOCK_METHOD0(resetWorld, void());
	MOCK_METHOD1(addNewObject, LightBulb::AbstractEvolutionObject* (bool));
	MOCK_METHOD0(getCombiningStrategy, LightBulb::AbstractCombiningStrategy* ());
	MOCK_METHOD0(getEvolutionObjects, std::vector<LightBulb::AbstractEvolutionObject*>* ());
	MOCK_METHOD1(setEvolutionObjects, void(std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD0(reset, void());
	MOCK_METHOD0(isParasiteWorld, bool());
	MOCK_METHOD0(getPopulationSize, int());
	MOCK_METHOD0(clearPopulation, void());
	MOCK_METHOD1(getScore, double(LightBulb::AbstractEvolutionObject*));
	MOCK_METHOD3(doCompare, int(LightBulb::AbstractEvolutionObject*, LightBulb::AbstractEvolutionObject*, int));

	MOCK_METHOD1(rateKI, int(LightBulb::AbstractEvolutionObject*));
	MOCK_METHOD1(setLogger, void(LightBulb::AbstractLogger*));
	MOCK_METHOD0(getDataSetLabels, std::vector<std::string>());
};

#endif
