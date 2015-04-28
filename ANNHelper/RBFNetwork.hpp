#pragma once

#ifndef _RBFNETWORK_H_
#define _RBFNETWORK_H_

// Libary includes

// Includes
#include "LayeredNetwork.hpp"

// Forward declarations


// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class RBFNetwork : public LayeredNetwork
{
private:	
public:
	RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer);		
};

#endif