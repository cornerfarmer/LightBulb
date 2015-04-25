#pragma once

#ifndef _FERMIFUNCTION_H_
#define _FERMIFUNCTION_H_

// Includes
#include "ActivationFunction.hpp"

class FermiFunction : public ActivationFunction
{
private:
	float temperatureParameter;
public:
	FermiFunction(float temperatureParameter_);
	float execute(float input, float threshold);
	float executeDerivation(float input, float threshold);
	ActivationFunction* getActivationFunctionCopy();
};

#endif