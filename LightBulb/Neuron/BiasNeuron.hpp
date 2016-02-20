#pragma once

#ifndef _BIASNEURON_H_
#define _BIASNEURON_H_

// Includes
#include "Neuron/InputNeuron.hpp"

// A BiasNeuron is a special neuron, which has always the output 1
class BiasNeuron : public InputNeuron
{
private:
public:	
	BiasNeuron();
	// Sets its activation always to 1
	void refreshActivation();	
	void resetActivation() {};
};

#endif