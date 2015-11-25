#pragma once

#ifndef _ABSTRACTSHRINKFUNCTION_H_
#define _ABSTRACTSHRINKFUNCTION_H_

// Forward declaration

// This abstract class describes a function, which returns a in time shrinking value
class AbstractShrinkFunction
{
protected:
	// The starting value
	double startValue;
	// The lowest possible value
	double minValue;
public:
	AbstractShrinkFunction(double startValue_, double minValue_);
	// Calculate the value in the given timestep
	virtual double execute(double time) = 0;
	// Create a copy of the object
	virtual AbstractShrinkFunction* getShrinkFunctionCopy() = 0;
};

#endif