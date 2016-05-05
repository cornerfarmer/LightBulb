#pragma once

#ifndef _MOCKHALLOFFAMEALGORITHM_H_
#define _MOCKHALLOFFAMEALGORITHM_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractHallOfFameAlgorithm.hpp>

class MockHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
{
public:
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD1(evaluateObjects, void (std::vector<AbstractEvolutionObject*>&));
	MOCK_METHOD1(addMember, void (AbstractEvolutionObject*));
	MOCK_METHOD2(execute, void (AbstractCoevolutionWorld*, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>&));
};

#endif
