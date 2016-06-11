#pragma once

#ifndef _MOCKEVOLUTIONWORLD_H_
#define _MOCKEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

class MockEvolutionWorld : public AbstractEvolutionWorld
{
public:
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD0(getEvolutionObjects, std::vector<AbstractEvolutionObject*>* ());
	MOCK_METHOD0(getHighscoreList, std::vector<std::pair<double, AbstractEvolutionObject*>>* ());
	MOCK_METHOD1(setEvolutionObjects, void (std::vector<AbstractEvolutionObject*>&));
	MOCK_METHOD1(addNewObject, AbstractEvolutionObject* (bool));
	MOCK_METHOD0(doSimulationStep, bool ());
	MOCK_METHOD0(getPopulationSize, int ());
	MOCK_METHOD1(getScore, double (AbstractEvolutionObject*));
	MOCK_METHOD1(getRealScore, double (AbstractEvolutionObject*));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD0(reset, void ());
	MOCK_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_METHOD0(releaseAllObjects, void ());
	MOCK_METHOD1(addExistingObject, void (AbstractEvolutionObject*));
};

#endif
