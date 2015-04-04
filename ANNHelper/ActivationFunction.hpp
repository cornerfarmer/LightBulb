#pragma once

#ifndef _ACTIVATIONFUNCTION_H_
#define _ACTIVATIONFUNCTION_H_

// This abstract class describes a function, which can calculate the activation of a neuron
class ActivationFunction
{
private:
public:
	// Calculate the activation from the given input
	virtual float execute(float input, float threshold) = 0;
};

#endif