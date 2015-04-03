#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "InputFunction.hpp"

// The WeightedSumFunction uses the weighted sum to calculate the input ;) 
class WeightedSumFunction : InputFunction
{
private:
public:
	WeightedSumFunction();
	// Calculates Σ output * weight
	float execute(std::list<Edge*> input);
};

#endif
