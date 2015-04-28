#pragma once

#ifndef _FERMIFUNCTION_H_
#define _FERMIFUNCTION_H_

// Includes
#include "AbstractActivationFunction.hpp"

class FermiFunction : public AbstractActivationFunction
{
private:
	float temperatureParameter;
public:
	FermiFunction(float temperatureParameter_);
	float execute(float input, AbstractThreshold* threshold);
	float executeDerivation(float input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool isLinear();
};

#endif