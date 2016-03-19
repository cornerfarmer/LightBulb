#pragma once

#ifndef _MOCKRECOMBINATIONSELECTOR_H_
#define _MOCKRECOMBINATIONSELECTOR_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractRecombinationSelector.hpp>

class MockRecombinationSelector : public AbstractRecombinationSelector
{
public:
	MOCK_METHOD2(selectForRecombination, void (int, std::vector<std::pair<double, AbstractEvolutionObject*>>*));
	MOCK_METHOD1(addObjectToRecombination, void (AbstractEvolutionObject*));
	MOCK_METHOD3(executeRecombinationSelection, void (int, std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::map<AbstractEvolutionObject*, int>*));
	MOCK_METHOD0(getRecombinationSelection, std::vector<AbstractEvolutionObject*>* ());
};

#endif
