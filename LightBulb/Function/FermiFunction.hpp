#pragma once

#ifndef _FERMIFUNCTION_H_
#define _FERMIFUNCTION_H_

// Includes
#include "Function\AbstractActivationFunction.hpp"

// The FermiFunction is a sigmoid function between 0 and 1 which can be adjusted with temperatureParameter
class FermiFunction : public AbstractActivationFunction
{
private:
	float temperatureParameter;
public:
	FermiFunction(float temperatureParameter_);
	// Inherited
	float execute(float input, AbstractThreshold* threshold);
	float executeDerivation(float input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool hasAMaxAndMinimum();
};

#endif