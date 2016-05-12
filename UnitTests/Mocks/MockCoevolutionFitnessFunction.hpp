#pragma once

#ifndef _MOCKCOEVOLUTIONFITNESSFUNCTION_H_
#define _MOCKCOEVOLUTIONFITNESSFUNCTION_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp>

class MockCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
{
public:
	MOCK_METHOD1(execute, std::map<AbstractEvolutionObject*, double>* (CombiningStrategyResults&));
};

#endif
