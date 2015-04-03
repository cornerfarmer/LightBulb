#include "InputNeuron.hpp"

InputNeuron::InputNeuron()
{
	input = 0;
}

void InputNeuron::setInput(float newInput)
{
	input = newInput;
}

void InputNeuron::refreshActivation()
{
	// Set the activation to the given input
	activation = input;
}