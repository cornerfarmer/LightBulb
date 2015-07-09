#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "Function\AbstractInputFunction.hpp"

//Forward declarations
class Edge;

// The WeightedSumFunction uses the weighted sum to calculate the input ;) 
class WeightedSumFunction : public AbstractInputFunction
{
private:
public:
	// Calculates Σ output * weight
	float execute(std::list<Edge*> &input, AbstractThreshold* threshold, float additionalInput, std::map<AbstractNeuron*, float>* neuronOutputCache = NULL);
	AbstractInputFunction* getInputFunctionCopy();
};

#endif
