#pragma once

#ifndef _HYPERBOLICTANGENTFUNCTION_H_
#define _HYPERBOLICTANGENTFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "AbstractActivationFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class HyperbolicTangentFunction : public AbstractActivationFunction
{
private:
public:
	// Just returns the given input
	float execute(float input, float threshold);
	// Returns always 0
	float executeDerivation(float input, float threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
};

#endif