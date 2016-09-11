#pragma once

#ifndef _MOCKCOMBININGSTRATEGY_H_
#define _MOCKCOMBININGSTRATEGY_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCombiningStrategy.hpp>

class MockCombiningStrategy : public LightBulb::AbstractCombiningStrategy
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator*));
	MOCK_METHOD3(combine, void (LightBulb::AbstractCoevolutionWorld*, std::vector<LightBulb::AbstractEvolutionObject*>*, std::vector<LightBulb::AbstractEvolutionObject*>*));
	MOCK_METHOD1(execute, LightBulb::CombiningStrategyResults* (LightBulb::AbstractCoevolutionWorld*));
	MOCK_METHOD1(setSecondWorld, void (LightBulb::AbstractCoevolutionWorld*));
	MOCK_METHOD0(getPrevResults, LightBulb::CombiningStrategyResults* ());
	MOCK_METHOD0(getFirstPlayerWins, int ());
	MOCK_METHOD1(getTotalMatches, int (LightBulb::AbstractCoevolutionWorld*));
};

#endif
