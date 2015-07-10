#pragma once

#ifndef _IDENTITYFUNCTION_H_
#define _IDENTITYFUNCTION_H_

// Includes
#include "Function\AbstractActivationFunction.hpp"
#include "Function\AbstractOutputFunction.hpp"

// The IdentityFunction just returns the input without calculating anything
class IdentityFunction : public AbstractOutputFunction, public AbstractActivationFunction
{
private:
public:
	// Inherited: 
	double execute(double input);
	double execute(double input, AbstractThreshold* threshold);
	double executeDerivation(double input, AbstractThreshold* threshold);
	AbstractOutputFunction* getOutputFunctionCopy();
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif