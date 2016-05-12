#pragma once

#ifndef _MOCKCOMBININGSTRATEGY_H_
#define _MOCKCOMBININGSTRATEGY_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCombiningStrategy.hpp>

class MockCombiningStrategy : public AbstractCombiningStrategy
{
public:
	MOCK_METHOD3(combine, void (AbstractCoevolutionWorld*, std::vector<AbstractEvolutionObject*>*, std::vector<AbstractEvolutionObject*>*));
	MOCK_METHOD0(getFirstPlayerWins, int ());
	MOCK_METHOD1(setSecondWorld, void (AbstractCoevolutionWorld*));
	MOCK_METHOD1(getTotalMatches, int (AbstractCoevolutionWorld*));
	MOCK_METHOD1(execute, CombiningStrategyResults* (AbstractCoevolutionWorld*));
	MOCK_METHOD0(getPrevResults, CombiningStrategyResults* ());
};

#endif
