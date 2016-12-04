#pragma once

#ifndef _MOCKSELECTIONFUNCTION_H_
#define _MOCKSELECTIONFUNCTION_H_

#include "gmock/gmock.h"
#include <LightBulb/Function/SelectionFunction/AbstractSelectionFunction.hpp>

class MockSelectionFunction : public LightBulb::AbstractSelectionFunction
{
public:
	MOCK_METHOD1(setRandomGenerator, void (LightBulb::AbstractRandomGenerator&));
	MOCK_CONST_METHOD1(execute, int (const std::vector<double>&));
	MOCK_CONST_METHOD2(execute, std::vector<int> (const std::vector<double>&, int));
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
