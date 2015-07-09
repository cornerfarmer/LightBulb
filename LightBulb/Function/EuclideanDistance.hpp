#pragma once

#ifndef _EUCLIDEANDISTANCEFUNCTION_H_
#define _EUCLIDEANDISTANCEFUNCTION_H_

// Includes
#include "Function\AbstractInputFunction.hpp"

//Forward declarations
class Edge;

// The EuclideanDistance calculates the dinstance between the input and the center of a RBF Neuron 
class EuclideanDistance : public AbstractInputFunction
{
private:
public:
	// Calculates sqrt( Σ (output - center)^2 )
	double execute(std::list<Edge*> &input, AbstractThreshold* threshold, double additionalInput, std::map<AbstractNeuron*, double>* neuronOutputCache = NULL);
	// Inherited:
	AbstractInputFunction* getInputFunctionCopy();
};

#endif
