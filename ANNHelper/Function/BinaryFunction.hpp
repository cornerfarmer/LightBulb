#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "AbstractActivationFunction.hpp"

// A binary function always has the value 0 or 1
class BinaryFunction : public AbstractActivationFunction
{
private:
public:
	// Returns 0 (input < threshold) or 1 (input > threshold)
	float execute(float input, AbstractThreshold* threshold);
	// Error - No derivation available
	float executeDerivation(float input, AbstractThreshold* threshold);
	// Inherited:
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool hasAMaxAndMinimum();
};

#endif