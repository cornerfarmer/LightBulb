#pragma once

#ifndef _MOCKRECOMBINATIONSELECTOR_H_
#define _MOCKRECOMBINATIONSELECTOR_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractRecombinationSelector.hpp>

class MockRecombinationSelector : public LightBulb::AbstractRecombinationSelector
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(addObjectToRecombination, void (LightBulb::AbstractEvolutionObject&));
	MOCK_METHOD2(selectForRecombination, void (int, const std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>&));
	MOCK_METHOD3(executeRecombinationSelection, void (int, const std::vector<std::pair<double, LightBulb::AbstractEvolutionObject*>>&, std::map<LightBulb::AbstractEvolutionObject*, int>&));
	MOCK_METHOD0(getRecombinationSelection, std::vector<LightBulb::AbstractEvolutionObject*>& ());
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
