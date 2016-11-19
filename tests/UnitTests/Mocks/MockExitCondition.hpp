#pragma once

#ifndef _MOCKEXITCONDITION_H_
#define _MOCKEXITCONDITION_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractExitCondition.hpp>

class MockExitCondition : public LightBulb::AbstractExitCondition
{
public:
	MOCK_METHOD1(setLogger, void (LightBulb::AbstractLogger&));
	MOCK_METHOD2(evaluate, bool (const std::vector<std::pair<double, LightBulb::AbstractIndividual*>>&, const LightBulb::AbstractEvolutionLearningRule&));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
