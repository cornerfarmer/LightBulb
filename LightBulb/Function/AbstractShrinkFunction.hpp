#pragma once

#ifndef _ABSTRACTSHRINKFUNCTION_H_
#define _ABSTRACTSHRINKFUNCTION_H_

// Forward declaration

// This abstract class describes a function, which can calculate the neighborhood factor in a som network
class AbstractShrinkFunction
{
protected:
	double startValue;
	double minValue;
public:
	AbstractShrinkFunction(double startValue_, double minValue_);
	// Calculate the neighborhood factor
	virtual double execute(double time) = 0;
	// Create a copy of the object
	virtual AbstractShrinkFunction* getShrinkFunctionCopy() = 0;
};

#endif