#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

// Libary includes
#include <vector>
#include <list>

// Includes
#include "NetworkTopology.hpp"
#include "Neuron.hpp"

// Forward declarations
class ActivationFunction;
class InputFunction;
class OutputFunction;

// This struct contains all options needed to build a LayeredNetwork
struct LayeredNetworkOptions
{
	ActivationFunction* activationFunction;
	InputFunction* inputFunction;
	OutputFunction* outputFunction;
	bool enableDirectBackCoupling;
	bool enableIndirectBackCoupling;
	bool enableLateralBackCoupling;
	bool enableShortcuts;
	std::vector<int> neuronsPerLayerCount;
};

typedef struct LayeredNetworkOptions LayeredNetworkOptions_t;

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : NetworkTopology
{
private:
	LayeredNetworkOptions_t options;
	std::list<std::list<Neuron>> neurons;
public:
	~LayeredNetwork();
	LayeredNetwork();
	LayeredNetwork(const LayeredNetworkOptions_t &options_);	
};

#endif