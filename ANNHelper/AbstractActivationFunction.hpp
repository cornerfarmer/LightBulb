#pragma once

#ifndef _ABSTRACTACTIVATIONFUNCTION_H_
#define _ABSTRACTACTIVATIONFUNCTION_H_

// This abstract class describes a function, which can calculate the activation of a neuron
class AbstractActivationFunction
{
private:
public:
	virtual ~AbstractActivationFunction() {}
	// Calculate the activation from the given input
	virtual float execute(float input, float threshold) = 0;
	virtual float executeDerivation(float input, float threshold) = 0;
	// Create a copy of the object
	virtual AbstractActivationFunction* getActivationFunctionCopy() = 0;
};

#endif