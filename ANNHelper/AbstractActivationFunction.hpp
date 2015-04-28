#pragma once

#ifndef _ABSTRACTACTIVATIONFUNCTION_H_
#define _ABSTRACTACTIVATIONFUNCTION_H_

// Forward declaration
class AbstractThreshold;

// This abstract class describes a function, which can calculate the activation of a neuron
class AbstractActivationFunction
{
private:
public:
	virtual ~AbstractActivationFunction() {}
	// Calculate the activation from the given input
	virtual float execute(float input, AbstractThreshold* threshold) = 0;
	virtual float executeDerivation(float input, AbstractThreshold* threshold) = 0;
	// Create a copy of the object
	virtual AbstractActivationFunction* getActivationFunctionCopy() = 0;
	virtual float getMaximum() = 0;
	virtual float getMinimum() = 0;
	virtual bool isLinear() = 0;
};

#endif