#pragma once

#ifndef _MOCKRANDOMGENERATOR_H_
#define _MOCKRANDOMGENERATOR_H_

#include "gmock/gmock.h"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"

class MockRandomGenerator : public LightBulb::AbstractRandomGenerator
{
public:
	MockRandomGenerator()
		: AbstractRandomGenerator(-1)
	{
		
	}

	MOCK_METHOD0(randFloat, float ());
	MOCK_METHOD2(randFloat, float (float, float));
	MOCK_METHOD2(randInt, int (int, int));
	MOCK_METHOD0(reset, void ());
	MOCK_CONST_METHOD0(getSeed, int ());
	MOCK_METHOD1(setSeed, void (int));
};

#endif
