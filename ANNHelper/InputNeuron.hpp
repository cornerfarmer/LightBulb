#pragma once

#ifndef _INPUTNEURON_H_
#define _INPUTNEURON_H_

// Includes
#include "AbstractNeuron.hpp"

// A InputNeuron is the interface between the NeuralNetwork and your input variables.
// It just can have efferent edges, no afferent edges! 
class InputNeuron : public AbstractNeuron
{
private:
	float input;
public:	
	InputNeuron();
	// Set the input value of the neuron
	void setInput(float newInput);
	// Sets the activation of the neuron to its input value
	void refreshActivation();
};

#endif