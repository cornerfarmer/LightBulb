#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class IdentityFunction : ActivationFunction, OutputFunction
{
private:
public:
	// Just returns the given input
	float execute(float input);
};

#endif