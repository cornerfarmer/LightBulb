#pragma once

#ifndef _MOCKRANDOMFUNCTION_H_
#define _MOCKRANDOMFUNCTION_H_

#include "gmock/gmock.h"
#include <LightBulb/Function/RandomFunction/AbstractRandomFunction.hpp>
#include <LightBulb/Random/AbstractRandomGenerator.hpp>

class MockRandomFunction : public LightBulb::AbstractRandomFunction
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_CONST_METHOD1(execute, int (int));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
