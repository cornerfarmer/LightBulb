#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "Function\AbstractActivationFunction.hpp"

// A binary function always has the value 0 or 1
class BinaryFunction : public AbstractActivationFunction
{
private:
public:
	// Returns 0 (input < threshold) or 1 (input > threshold)
	double execute(double input, AbstractThreshold* threshold);
	// Error - No derivation available
	double executeDerivation(double input, AbstractThreshold* threshold);
	// Inherited:
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif