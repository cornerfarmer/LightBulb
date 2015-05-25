#pragma once

#ifndef _EUCLIDEANDISTANCEFUNCTION_H_
#define _EUCLIDEANDISTANCEFUNCTION_H_

// Includes
#include "AbstractInputFunction.hpp"

//Forward declarations
class Edge;

// The EuclideanDistance calculates the dinstance between the input and the center of a RBF Neuron 
class EuclideanDistance : public AbstractInputFunction
{
private:
public:
	// Calculates sqrt( Σ (output - center)^2 )
	float execute(std::list<Edge*> &input, AbstractThreshold* threshold);
	AbstractInputFunction* getInputFunctionCopy();
};

#endif
