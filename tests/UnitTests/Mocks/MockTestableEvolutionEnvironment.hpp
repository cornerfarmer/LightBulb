#pragma once

#ifndef _MOCKTESTABLEEVOLUTIONENVIRONMENT_H_
#define _MOCKTESTABLEEVOLUTIONENVIRONMENT_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp>

class MockTestableEvolutionEnvironment : public LightBulb::AbstractEvolutionEnvironment
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD0(getIndividuals, std::vector<LightBulb::AbstractIndividual*>& ());
	MOCK_METHOD1(setIndividuals, void (const std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD1(addNewIndividual, LightBulb::AbstractIndividual* (bool));
	MOCK_METHOD0(doSimulationStep, void ());
	MOCK_CONST_METHOD1(getFitness, double (const LightBulb::AbstractIndividual&));
	MOCK_METHOD0(initializeForLearning, void ());
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getDataSetLabels, std::vector<std::string> ());
	MOCK_CONST_METHOD0(getPopulationSize, int ());
	MOCK_METHOD0(clearPopulation, void ());
	MOCK_METHOD1(addExistingIndividual, void (LightBulb::AbstractIndividual*));
};

#endif
