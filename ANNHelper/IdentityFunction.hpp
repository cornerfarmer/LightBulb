#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "AbstractActivationFunction.hpp"
#include "AbstractOutputFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class IdentityFunction : public AbstractOutputFunction, public AbstractActivationFunction
{
private:
public:
	// Just returns the given input
	float execute(float input);
	float execute(float input, float threshold);
	// Returns always 0
	float executeDerivation(float input, float threshold);
	AbstractOutputFunction* getOutputFunctionCopy();
	AbstractActivationFunction* getActivationFunctionCopy();
};

#endif