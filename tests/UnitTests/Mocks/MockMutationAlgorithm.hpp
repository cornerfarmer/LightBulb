#pragma once

#ifndef _MOCKMUTATIONALGORITHM_H_
#define _MOCKMUTATIONALGORITHM_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp>

class MockMutationAlgorithm : public LightBulb::AbstractMutationAlgorithm
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD1(execute, void (LightBulb::AbstractIndividual&));
	MOCK_METHOD1(initialize, void (const std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
