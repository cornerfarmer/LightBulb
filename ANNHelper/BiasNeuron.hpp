#pragma once

#ifndef _BIASNEURON_H_
#define _BIASNEURON_H_

// Includes
#include "InputNeuron.hpp"

// A BiasNeuron is a special neuron, which has always the output 1
class BiasNeuron : InputNeuron
{
private:
public:	
	BiasNeuron();
	// Sets its activation always to 1
	void refreshActivation();
};

#endif