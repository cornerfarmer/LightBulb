#pragma once

#ifndef _GAUSSIANRBFFUNCTION_H_
#define _GAUSSIANRBFFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function\AbstractActivationFunction.hpp"
#include "Function\AbstractNeighborhoodFunction.hpp"

class GaussianRBFFunction : public AbstractActivationFunction, public AbstractNeighborhoodFunction
{
private:
public:
	// Inherited:
	double execute(double input, AbstractThreshold* threshold);
	double executeDerivation(double input, AbstractThreshold* threshold);
	AbstractActivationFunction* getActivationFunctionCopy();
	double getMaximum();
	double getMinimum();
	bool hasAMaxAndMinimum();
	double execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance);
	AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy();
};

#endif