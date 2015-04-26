#pragma once

#ifndef _ABSTRACTINPUTFUNCTION_H_
#define _ABSTRACTINPUTFUNCTION_H_

// Includes
#include <vector>

// Forward declarations
class Edge;

// An InputFunction calculates one input value from the output of all previous neurons
class AbstractInputFunction
{
private:
public:
	virtual ~AbstractInputFunction() {}
	// Calculate the one value from all given afferent edges
	virtual float execute(std::vector<Edge*> &input) = 0;
	// Create a copy of the object
	virtual AbstractInputFunction* getInputFunctionCopy() = 0;
};

#endif