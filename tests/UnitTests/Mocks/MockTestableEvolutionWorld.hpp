#pragma once

#ifndef _MOCKTESTABLEEVOLUTIONWORLD_H_
#define _MOCKTESTABLEEVOLUTIONWORLD_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractEvolutionWorld.hpp>

class MockTestableEvolutionWorld : public LightBulb::AbstractEvolutionWorld
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD0(getIndividuals, std::vector<LightBulb::AbstractIndividual*>& ());
	MOCK_METHOD1(setIndividuals, void (const std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD1(addNewIndividual, LightBulb::AbstractIndividual* (bool));
	MOCK_METHOD0(doSimulationStep, bool ());
	MOCK_CONST_METHOD1(getScore, double (const LightBulb::AbstractIndividual&));
	MOCK_CONST_METHOD1(getRealScore, double (const LightBulb::AbstractIndividual&));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(addExistingIndividual, void (LightBulb::AbstractIndividual*));
};

#endif
