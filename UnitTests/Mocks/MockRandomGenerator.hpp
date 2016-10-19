#pragma once

#ifndef _MOCKRANDOMGENERATOR_H_
#define _MOCKRANDOMGENERATOR_H_

#include "gmock/gmock.h"
#include "Random/AbstractRandomGenerator.hpp"

class MockRandomGenerator : public LightBulb::AbstractRandomGenerator
{
public:
	MOCK_METHOD0(randDouble, double ());
	MOCK_METHOD2(randDouble, double (double, double));
	MOCK_METHOD2(randInt, int (int, int));
	MOCK_CONST_METHOD0(getSeed, int ());
	MOCK_METHOD1(setSeed, void (int));
};

#endif
