#pragma once

#ifndef _HYPERBOLICTANGENTFUNCTION_H_
#define _HYPERBOLICTANGENTFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/AbstractActivationFunction.hpp"

// The HyperbolicTangentFunction is a sigmoid function between -1 and 1
class HyperbolicTangentFunction : public AbstractActivationFunction
{
private:
public:
	// Inherited
	double execute(double input);
	double executeDerivation(double input);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif