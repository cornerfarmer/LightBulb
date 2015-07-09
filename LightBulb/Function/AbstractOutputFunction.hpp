#pragma once

#ifndef _ABSTRACTOUTPUTFUNCTION_H_
#define _ABSTRACTOUTPUTFUNCTION_H_

// An OutputFunction calculates the output of a neuron from its activation
class AbstractOutputFunction
{
private:
public:
	virtual ~AbstractOutputFunction() {}
	// Calculate the output from the activation
	virtual double execute(double activation) = 0;
	// Create a copy of the object
	virtual AbstractOutputFunction* getOutputFunctionCopy() = 0;
};

#endif