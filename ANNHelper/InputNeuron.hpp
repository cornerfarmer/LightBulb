#pragma once

#ifndef _INPUTNEURON_H_
#define _INPUTNEURON_H_

// Includes
#include "Neuron.hpp"

// A InputNeuron is the interface between the NeuralNetwork and your input variables.
// It just can have efferent edges, no afferent edges! 
class InputNeuron : Neuron
{
private:
	float input;
public:	
	InputNeuron();
	void setInput(float newInput);
	void refreshActivation();
};

#endif