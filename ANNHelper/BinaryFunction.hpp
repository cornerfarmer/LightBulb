#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "AbstractActivationFunction.hpp"

class BinaryFunction : public AbstractActivationFunction
{
private:
public:
	// Returns 0 or 1
	float execute(float input, float threshold);
	// Error - No derivation available
	float executeDerivation(float input, float threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool isLinear();
};

#endif