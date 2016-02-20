#pragma once

#ifndef _COSINUSFUNCTION_H_
#define _COSINUSFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/AbstractNeighborhoodFunction.hpp"

// Describes a neighborhood relation in form of a cos curve
class CosinusFunction : public AbstractNeighborhoodFunction
{
private:
public:
	// Inherited:	
	double execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance);
	AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy();
};

#endif