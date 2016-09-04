#pragma once

#ifndef _HYPERBOLICTANGENTFUNCTION_H_
#define _HYPERBOLICTANGENTFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"

// The HyperbolicTangentFunction is a sigmoid function between -1 and 1
class HyperbolicTangentFunction : public AbstractActivationFunction
{
private:
public:
	// Inherited
	double execute(double input) override;
	double executeDerivation(double input) override;
	AbstractActivationFunction* getActivationFunctionCopy() override;
	double getMaximum() override;
	double getMinimum() override;
	bool hasAMaxAndMinimum() override;
};

#endif