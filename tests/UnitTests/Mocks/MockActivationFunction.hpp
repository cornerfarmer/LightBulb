#pragma once

#ifndef _MOCKACTIVATIONFUNCTION_H_
#define _MOCKACTIVATIONFUNCTION_H_

#include "gmock/gmock.h"
#include <LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp>

class MockActivationFunction : public LightBulb::AbstractActivationFunction
{
public:
	MOCK_CONST_METHOD3(execute, void (int, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>&, const std::vector<Eigen::VectorXd>&));
	MOCK_CONST_METHOD1(execute, double (double));
	MOCK_CONST_METHOD1(executeDerivation, double (double));
	MOCK_CONST_METHOD1(executeDerivation, Eigen::VectorXd (const Eigen::VectorXd&));
	MOCK_CONST_METHOD0(getMaximum, double ());
	MOCK_CONST_METHOD0(getMinimum, double ());
	MOCK_CONST_METHOD0(hasAMaxAndMinimum, bool ());
	MOCK_CONST_METHOD0(clone, AbstractCloneable* ());
};

#endif
