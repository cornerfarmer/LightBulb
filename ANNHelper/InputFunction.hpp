#pragma once

#ifndef _INPUTFUNCTION_H_
#define _INPUTFUNCTION_H_

// Includes
#include <list>

// Forward declarations
class Edge;

// An InputFunction calculates one input value from the output of all previous neurons
class InputFunction
{
private:
public:
	virtual float execute(std::list<Edge*> input) = 0;
};

#endif