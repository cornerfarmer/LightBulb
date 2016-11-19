#pragma once

#ifndef _MOCKCOEVOLUTIONFITNESSFUNCTION_H_
#define _MOCKCOEVOLUTIONFITNESSFUNCTION_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp>

class MockCoevolutionFitnessFunction : public LightBulb::AbstractCoevolutionFitnessFunction
{
public:
	MOCK_METHOD1(execute, std::map<const LightBulb::AbstractIndividual*, double>* (const LightBulb::CombiningStrategyResults&));
};

#endif
