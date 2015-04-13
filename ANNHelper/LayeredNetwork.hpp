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
	bool useBiasNeurons;
	std::vector<int> neuronsPerLayerCount;
	LayeredNetworkOptions()
	{
		enableDirectBackCoupling = false;
		enableIndirectBackCoupling = false;
		enableLateralBackCoupling = false;
		enableShortcuts = false;
		activationFunction = NULL;
		inputFunction = NULL;
		outputFunction = NULL;
		neuronsPerLayerCount = std::vector<int>();
		useBiasNeurons = false;
	}
};

typedef struct LayeredNetworkOptions LayeredNetworkOptions_t;

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : public NetworkTopology
{
private:
	LayeredNetworkOptions_t options;
	std::list<std::list<Neuron*>> neurons;
public:
	~LayeredNetwork();
	LayeredNetwork(const LayeredNetworkOptions_t &options_);	
	// Returns all InputNeurons (first layer)
	std::list<Neuron*>* getInputNeurons();
	// Returns all OutputNeurons (last layer)
	std::list<Neuron*>* getOutputNeurons();
	// Returns all Neurons of the selected layer
	std::list<Neuron*>* getNeuronsInLayer(int layerNr);
	// Calculates the layer count
	int getLayerCount();
	// Returns all Neurons
	std::list<std::list<Neuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(float randStart, float randEnd);
};

#endif