#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "Function\AbstractActivationFunction.hpp"

// A binary function always has the value 0 or 1
class BinaryFunction : public AbstractActivationFunction
{
private:
	double minValue;
	double maxValue;
public:
	BinaryFunction(double minValue_ = 0, double maxValue_ = 1);
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