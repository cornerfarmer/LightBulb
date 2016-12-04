#pragma once

#ifndef _MOCKRECOMBINATIONALGORITHM_H_
#define _MOCKRECOMBINATIONALGORITHM_H_

#include "gmock/gmock.h"
#include <LightBulb/Learning/Evolution/AbstractRecombinationAlgorithm.hpp>

class MockRecombinationAlgorithm : public LightBulb::AbstractRecombinationAlgorithm
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_METHOD2(execute, void (LightBulb::AbstractIndividual&, LightBulb::AbstractIndividual&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
