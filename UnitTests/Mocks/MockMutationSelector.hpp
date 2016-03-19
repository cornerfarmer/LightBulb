#pragma once

#ifndef _MOCKMUTATIONSELECTOR_H_
#define _MOCKMUTATIONSELECTOR_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractMutationSelector.hpp>

class MockMutationSelector : public AbstractMutationSelector
{
public:
	MOCK_METHOD1(addObjectToMutate, void (AbstractEvolutionObject*));
	MOCK_METHOD3(executeMutationSelection, void (int, std::vector<std::pair<double, AbstractEvolutionObject*>>*, std::map<AbstractEvolutionObject*, int>*));
	MOCK_METHOD0(getMutationSelection, std::vector<AbstractEvolutionObject*>* ());
	MOCK_METHOD2(selectForMutation, void (int, std::vector<std::pair<double, AbstractEvolutionObject*>>*));
};

#endif
