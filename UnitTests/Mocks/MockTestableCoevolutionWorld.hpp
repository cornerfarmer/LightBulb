#pragma once

#ifndef _MOCKTESTABLECOEVOLUTIONWORLD_H_
#define _MOCKTESTABLECOEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionWorld.hpp>

class MockTestableCoevolutionWorld : public AbstractCoevolutionWorld
{
public:
	MockTestableCoevolutionWorld(bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
		: AbstractCoevolutionWorld(isParasiteWorld_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
	{
	}
	MOCK_METHOD0(getHighscoreList, std::vector<std::pair<double, AbstractEvolutionObject*>>* ());
	MOCK_METHOD1(getRealScore, double (AbstractEvolutionObject*));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(createNewObject, AbstractEvolutionObject* ());
	MOCK_METHOD0(resetWorld, void ());
	MOCK_METHOD1(addNewObject, AbstractEvolutionObject* (bool));
	MOCK_METHOD0(getCombiningStrategy, AbstractCombiningStrategy* ());
	MOCK_METHOD0(getEvolutionObjects, std::vector<AbstractEvolutionObject*>* ());
	MOCK_METHOD1(setEvolutionObjects, void (std::vector<AbstractEvolutionObject*>&));
	MOCK_METHOD0(reset, void ());
	MOCK_METHOD0(isParasiteWorld, bool ());
	MOCK_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(getScore, double (AbstractEvolutionObject*));
	MOCK_METHOD2(compareObjects, int (AbstractEvolutionObject*, AbstractEvolutionObject*));
	MOCK_METHOD1(rateKI, int (AbstractEvolutionObject*));
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD0(getDataSetLabels, std::vector<std::string> ());
};

#endif
