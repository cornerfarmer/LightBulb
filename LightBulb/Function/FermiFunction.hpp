#pragma once

#ifndef _FERMIFUNCTION_H_
#define _FERMIFUNCTION_H_

// Includes
#include "Function\AbstractActivationFunction.hpp"

// The FermiFunction is a sigmoid function between 0 and 1 which can be adjusted with temperatureParameter
class FermiFunction : public AbstractActivationFunction
{
private:
	double temperatureParameter;
public:
	FermiFunction(double temperatureParameter_);
	// Inherited
	double execute(double input, AbstractThreshold* threshold);
	double executeDerivation(double input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
};

#endif