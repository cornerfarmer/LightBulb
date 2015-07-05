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
	// Inherited: 
	float execute(float input);
	float execute(float input, AbstractThreshold* threshold);
	float executeDerivation(float input, AbstractThreshold* threshold);
	AbstractOutputFunction* getOutputFunctionCopy();
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool hasAMaxAndMinimum();
};

#endif