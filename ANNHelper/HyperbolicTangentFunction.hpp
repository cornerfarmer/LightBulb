#pragma once

#ifndef _HYPERBOLICTANGENTFUNCTION_H_
#define _HYPERBOLICTANGENTFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "ActivationFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class HyperbolicTangentFunction : public ActivationFunction
{
private:
public:
	// Just returns the given input
	float execute(float input, float threshold);
	// Returns always 0
	float executeDerivation(float input, float threshold);
};

#endif