#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "Function/AbstractActivationFunction.hpp"

// A binary function can decide between two values
class BinaryFunction : public AbstractActivationFunction
{
private:
	// The two possible values
	double minValue;
	double maxValue;
public:
	BinaryFunction(double minValue_ = 0, double maxValue_ = 1);
	// Returns minValue (input < threshold) or maxValue (input > threshold)
	double execute(double input);
	// Error - No derivation available
	double executeDerivation(double input);
	// Inherited:
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif