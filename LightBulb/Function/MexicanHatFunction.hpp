#pragma once

#ifndef _MEXICANHATFUNCTION_H_
#define _MEXICANHATFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function\AbstractNeighborhoodFunction.hpp"

class MexicanHatFunction : public AbstractNeighborhoodFunction
{
private:
public:
	// Inherited:	
	double execute(StandardNeuron* neuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance);
	AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy();
};

#endif