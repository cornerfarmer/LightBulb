#pragma once

#ifndef _INPUTNEURON_H_
#define _INPUTNEURON_H_

// Includes
#include "Neuron/AbstractNeuron.hpp"

// A InputNeuron is the interface between the NeuralNetwork and your input variables.
// It just can have efferent edges, no afferent edges! 
class InputNeuron : public AbstractNeuron
{
private:
public:	
	InputNeuron();
	// Set the input value of the neuron
	void setInput(double newInput);
	// Sets the activation of the neuron to its input value
	void refreshActivation() {};
	// Do nothing, a inputNeuron does not have a netInput
	void refreshNetInput(std::map<AbstractNeuron*, double>* neuronOutputCache = NULL) {};
	void resetActivation() {};
};

#endif