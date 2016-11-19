#pragma once

#ifndef _MOCKFITNESSFUNCTION_H_
#define _MOCKFITNESSFUNCTION_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractFitnessFunction.hpp>

class MockFitnessFunction : public LightBulb::AbstractFitnessFunction
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD1(execute, void (std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
