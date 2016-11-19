#pragma once

#ifndef _MOCKCOMBININGSTRATEGY_H_
#define _MOCKCOMBININGSTRATEGY_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCombiningStrategy.hpp>

class MockCombiningStrategy : public LightBulb::AbstractCombiningStrategy
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD3(combine, void (LightBulb::AbstractCoevolutionEnvironment&, std::vector<LightBulb::AbstractIndividual*>&, std::vector<LightBulb::AbstractIndividual*>&));
	MOCK_METHOD1(execute, LightBulb::CombiningStrategyResults& (LightBulb::AbstractCoevolutionEnvironment&));
	MOCK_METHOD1(setSecondEnvironment, void (LightBulb::AbstractCoevolutionEnvironment&));
	MOCK_CONST_METHOD0(getPrevResults, const LightBulb::CombiningStrategyResults& ());
	MOCK_CONST_METHOD0(getFirstPlayerWins, int ());
	MOCK_CONST_METHOD1(getTotalMatches, int (const LightBulb::AbstractCoevolutionEnvironment&));
};

#endif
