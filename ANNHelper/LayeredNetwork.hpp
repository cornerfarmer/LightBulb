#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

#include <vector>
#include <list>

#include "NetworkTopology.hpp"
#include "Neuron.hpp"

class ActivationFunction;
class InputFunction;
class OutputFunction;

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