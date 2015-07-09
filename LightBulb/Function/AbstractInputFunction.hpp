#pragma once

#ifndef _ABSTRACTINPUTFUNCTION_H_
#define _ABSTRACTINPUTFUNCTION_H_

// Includes
#include <list>
#include <map>

// Forward declarations
class Edge;
class AbstractThreshold;
class AbstractNeuron;

// An InputFunction calculates one input value from the output of all previous neurons
class AbstractInputFunction
{
private:
public:
	virtual ~AbstractInputFunction() {}
	// Calculate the one value from all given input edges and the additional input.
	// The neuronOutputCache can be used do use a cached activation instead of the real/current one.
	virtual double execute(std::list<Edge*> &input, AbstractThreshold* threshold, double additionalInput, std::map<AbstractNeuron*, double>* neuronOutputCache = NULL) = 0;
	// Create a copy of the object
	virtual AbstractInputFunction* getInputFunctionCopy() = 0;
};

#endif