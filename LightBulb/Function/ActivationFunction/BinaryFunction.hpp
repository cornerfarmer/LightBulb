#pragma once

#ifndef _BINARYFUNCTION_H_
#define _BINARYFUNCTION_H_

// Includes
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include <IO/UseParentSerialization.hpp>

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
	double execute(double input) override;
	// Error - No derivation available
	double executeDerivation(double input) override;
	// Inherited:
	AbstractActivationFunction* getActivationFunctionCopy() override;
	double getMaximum() override;
	double getMinimum() override;
	bool hasAMaxAndMinimum() override;
};

EMPTY_CHILD_SERIALIZATION(BinaryFunction);

#endif