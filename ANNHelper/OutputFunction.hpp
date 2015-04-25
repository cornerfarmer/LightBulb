#pragma once

#ifndef _OUTPUTFUNCTION_H_
#define _OUTPUTFUNCTION_H_

// An OutputFunction calculates the output of a neuron from its activation
class OutputFunction
{
private:
public:
	virtual ~OutputFunction() {}
	// Calculate the output from the activation
	virtual float execute(float activation) = 0;
	// Create a copy of the object
	virtual OutputFunction* getOutputFunctionCopy() = 0;
};

#endif