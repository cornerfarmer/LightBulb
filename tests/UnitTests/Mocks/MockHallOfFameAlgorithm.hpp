#pragma once

#ifndef _MOCKHALLOFFAMEALGORITHM_H_
#define _MOCKHALLOFFAMEALGORITHM_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractHallOfFameAlgorithm.hpp>

class MockHallOfFameAlgorithm : public LightBulb::AbstractHallOfFameAlgorithm
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD1(evaluateObjects, void (std::vector<LightBulb::AbstractEvolutionObject*>&));
	MOCK_METHOD2(execute, void (LightBulb::AbstractCoevolutionWorld&, LightBulb::CombiningStrategyResults&));
	MOCK_METHOD1(addMember, void (LightBulb::AbstractEvolutionObject*));
};

#endif
