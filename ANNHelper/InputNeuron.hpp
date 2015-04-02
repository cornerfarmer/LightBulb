#pragma once

#ifndef _INPUTNEURON_H_
#define _INPUTNEURON_H_

#include "Neuron.hpp"

class InputNeuron : Neuron
{
private:
	float input;
public:	
	InputNeuron();
	void setInput(float newInput);
};

#endif