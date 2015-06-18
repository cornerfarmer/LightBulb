#pragma once

#ifndef _CASCADECORRELATIONNETWORK_H_
#define _CASCADECORRELATIONNETWORK_H_

// Libary includes

// Includes
#include "LayeredNetwork.hpp"

// Forward declarations


// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class CascadeCorrelationNetwork : public LayeredNetwork
{
private:	
public:
	CascadeCorrelationNetwork(unsigned int inputNeuronCount, unsigned int outputNeuronCount);		
	
};

#endif