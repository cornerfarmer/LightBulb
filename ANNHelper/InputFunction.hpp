#pragma once

#ifndef _INPUTFUNCTION_H_
#define _INPUTFUNCTION_H_

// Includes
#include <vector>

// Forward declarations
class Edge;

// An InputFunction calculates one input value from the output of all previous neurons
class InputFunction
{
private:
public:
	// Calculate the one value from all given afferent edges
	virtual float execute(std::vector<Edge*> &input) = 0;
};

#endif