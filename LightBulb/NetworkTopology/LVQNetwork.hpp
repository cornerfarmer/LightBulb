#pragma once

#ifndef _LVQNETWORK_H_
#define _LVQNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology\LayeredNetwork.hpp"

// Forward declarations


// A LVQNetwork is layered network which has only one input and one output layer.
class LVQNetwork : public LayeredNetwork
{
private:	
public:
	// Create a new CascadeCorrelationNetwork with the given input and output size
	LVQNetwork(unsigned int inputNeuronCount, unsigned int outputNeuronCount);	
};

#endif