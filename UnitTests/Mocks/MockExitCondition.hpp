#pragma once

#ifndef _MOCKEXITCONDITION_H_
#define _MOCKEXITCONDITION_H_

#include "gmock/gmock.h"
#include <Learning/Evolution/AbstractExitCondition.hpp>

class MockExitCondition : public AbstractExitCondition
{
public:
	MOCK_METHOD1(setLogger, void (AbstractLogger*));
	MOCK_METHOD2(evaluate, bool (std::vector<std::pair<double, AbstractEvolutionObject*>>*, AbstractEvolutionLearningRule*));
};

#endif
