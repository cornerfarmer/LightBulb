#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function\AbstractActivationFunction.hpp"

class GaussianRBFFunction : public AbstractActivationFunction
{
private:
public:
	// Inherited:
	float execute(float input, AbstractThreshold* threshold);
	float executeDerivation(float input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	float getMaximum();
	float getMinimum();
	bool hasAMaxAndMinimum();
};

#endif