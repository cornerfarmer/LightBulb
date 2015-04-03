#pragma once

#ifndef _OUTPUTFUNCTION_H_
#define _OUTPUTFUNCTION_H_

// An OutputFunction calculates the output of a neuron from its activation
class OutputFunction
{
private:
public:
	// Calculate the output from the activation
	virtual float execute(float activation) = 0;
};

#endif