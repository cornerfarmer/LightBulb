#pragma once

#ifndef _MOCKSELECTIONFUNCTION_H_
#define _MOCKSELECTIONFUNCTION_H_

#include "gmock/gmock.h"
#include <Function/SelectionFunction/AbstractSelectionFunction.hpp>

class MockSelectionFunction : public AbstractSelectionFunction
{
public:
	MOCK_METHOD1(execute, int (const std::vector<double>&));
	MOCK_METHOD2(execute, std::vector<int> (const std::vector<double>&, int));
};

#endif
