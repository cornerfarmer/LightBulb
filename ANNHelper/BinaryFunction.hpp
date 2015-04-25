#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "ActivationFunction.hpp"

class BinaryFunction : public ActivationFunction
{
private:
public:
	// Returns 0 or 1
	float execute(float input, float threshold);
	// Error - No derivation available
	float executeDerivation(float input, float threshold);
	ActivationFunction* getActivationFunctionCopy();
};

#endif