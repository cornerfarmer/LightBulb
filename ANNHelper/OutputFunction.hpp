#pragma once

#ifndef _OUTPUTFUNCTION_H_
#define _OUTPUTFUNCTION_H_

// An OutputFunction calculates the output of a neuron from its activation
class OutputFunction
{
private:
public:
	virtual float execute(float input) = 0;
};

#endif