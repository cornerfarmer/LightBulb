#pragma once

#ifndef _CYLINDERFUNCTION_H_
#define _CYLINDERFUNCTION_H_

// Library includes
#include <math.h>

// Includes
#include "Function/AbstractNeighborhoodFunction.hpp"

namespace LightBulb
{
	// Describes a neighborhood relation in form of a cylinder
	class CylinderFunction : public AbstractNeighborhoodFunction
	{
	private:
	public:
		// Inherited:	
		double execute(StandardNeuron* neuron, StandardNeuron* activatedNeuron, AbstractSOMStructure* structure, NeuronCompareThreshold* threshold, double maxDistance);
		AbstractNeighborhoodFunction* getNeighborhoodFunctionCopy();
	};
}

#endif