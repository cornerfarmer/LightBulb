#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "InputFunction.hpp"

//Forward declarations
class Edge;

// The WeightedSumFunction uses the weighted sum to calculate the input ;) 
class WeightedSumFunction : public InputFunction
{
private:
public:
	// Calculates Σ output * weight
	float execute(std::vector<Edge*> &input);
	InputFunction* getInputFunctionCopy();
};

#endif
