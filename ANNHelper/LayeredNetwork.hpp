#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

// Libary includes
#include <vector>


// Includes
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"

// Forward declarations
class AbstractNeuronFactory;

// This struct contains all options needed to build a LayeredNetwork
struct LayeredNetworkOptions
{	
	AbstractNeuronFactory* neuronFactory;
	bool enableDirectBackCoupling;
	bool enableIndirectBackCoupling;
	bool enableLateralBackCoupling;
	bool enableShortcuts;
	bool useBiasNeurons;
	std::vector<unsigned int> neuronsPerLayerCount;
	LayeredNetworkOptions();
	~LayeredNetworkOptions();
};

typedef struct LayeredNetworkOptions LayeredNetworkOptions_t;

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : public AbstractNetworkTopology
{
private:
	LayeredNetworkOptions_t* options;
	std::vector<std::vector<AbstractNeuron*>> neurons;
public:
	~LayeredNetwork();
	LayeredNetwork(LayeredNetworkOptions_t* options_);	
	// Returns all InputNeurons (first layer)
	std::vector<AbstractNeuron*>* getInputNeurons();
	// Returns all OutputNeurons (last layer)
	std::vector<AbstractNeuron*>* getOutputNeurons();
	// Returns all Neurons of the selected layer
	std::vector<AbstractNeuron*>* getNeuronsInLayer(int layerNr);
	// Calculates the layer count
	int getLayerCount();
	// Returns all Neurons
	std::vector<std::vector<AbstractNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(float randStart, float randEnd);
	// Calculates the Edge count
	int getEdgeCount();
};

#endif