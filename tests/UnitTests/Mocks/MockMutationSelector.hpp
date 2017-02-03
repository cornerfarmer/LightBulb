#pragma once

#ifndef _MOCKMUTATIONSELECTOR_H_
#define _MOCKMUTATIONSELECTOR_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractMutationSelector.hpp>
#include <LightBulb/Learning/Evolution/AbstractIndividual.hpp>
#include <LightBulb/Random/AbstractRandomGenerator.hpp>

class MockMutationSelector : public LightBulb::AbstractMutationSelector
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(addIndividualToMutate, void (LightBulb::AbstractIndividual&));
	MOCK_METHOD2(selectForMutation, void (int, const std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&));
	MOCK_METHOD3(executeMutationSelection, void (int, const std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&, std::map<LightBulb::AbstractIndividual*, int>&));
	MOCK_METHOD0(getMutationSelection, std::vector<LightBulb::AbstractIndividual*>& ());
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
