#pragma once

#ifndef _MOCKACTIVATIONFUNCTION_H_
#define _MOCKACTIVATIONFUNCTION_H_

#include "gmock/gmock.h"
#include <Function/ActivationFunction/AbstractActivationFunction.hpp>

class MockActivationFunction : public AbstractActivationFunction
{
public:
	MOCK_METHOD3(execute, void (int, std::vector<Eigen::VectorXd>&, std::vector<Eigen::VectorXd>&));
	MOCK_METHOD1(execute, double (double));
	MOCK_METHOD1(executeDerivation, double (double));
	MOCK_METHOD0(getActivationFunctionCopy, AbstractActivationFunction* ());
	MOCK_METHOD0(getMaximum, double ());
	MOCK_METHOD0(getMinimum, double ());
	MOCK_METHOD0(hasAMaxAndMinimum, bool ());
};

#endif
