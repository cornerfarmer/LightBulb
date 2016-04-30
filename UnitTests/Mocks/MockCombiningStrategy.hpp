#pragma once

#ifndef _MOCKCOMBININGSTRATEGY_H_
#define _MOCKCOMBININGSTRATEGY_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCombiningStrategy.hpp>

class MockCombiningStrategy : public AbstractCombiningStrategy
{
public:
	MOCK_METHOD3(combine, void (AbstractCoevolutionWorld*, std::vector<AbstractEvolutionObject*>*, std::vector<AbstractEvolutionObject*>*));
	MOCK_METHOD1(setSecondWorld, void (AbstractCoevolutionWorld*));
	MOCK_METHOD0(getPrevResults, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>* ());
	MOCK_METHOD1(getTotalMatches, int (AbstractCoevolutionWorld*));
};

#endif
