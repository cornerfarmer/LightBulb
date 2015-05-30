#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

// Libary includes
#include <vector>

// Includes
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "BiasNeuron.hpp"

// Forward declarations
class AbstractNeuronFactory;

// This struct contains all options needed to build a LayeredNetwork
struct LayeredNetworkOptions
{	
	AbstractNeuronFactory* neuronFactory;
	bool enableShortcuts;
	bool useBiasNeuron;
	std::vector<unsigned int> neuronsPerLayerCount;
	LayeredNetworkOptions();
	~LayeredNetworkOptions();
	LayeredNetworkOptions::LayeredNetworkOptions(const LayeredNetworkOptions &obj);
};

typedef struct LayeredNetworkOptions LayeredNetworkOptions_t;

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : public AbstractNetworkTopology
{
protected:
	std::unique_ptr<LayeredNetworkOptions_t> options;
	std::vector<std::vector<AbstractNeuron*>> neurons;
	BiasNeuron biasNeuron;
	void buildNetwork();	
	void refreshNeuronsPerLayerCounters();
public:
	~LayeredNetwork();
	LayeredNetwork(LayeredNetworkOptions_t &options_);	
	LayeredNetwork();	
	// Returns all InputNeurons (first layer)
	std::vector<AbstractNeuron*>* getInputNeurons();
	// Returns all OutputNeurons (last layer)
	std::vector<AbstractNeuron*>* getOutputNeurons();
	// Returns all Neurons of the selected layer
	std::vector<AbstractNeuron*>* getNeuronsInLayer(int layerIndex);
	// Calculates the layer count
	int getLayerCount();
	// Returns all Neurons
	std::vector<std::vector<AbstractNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(float randStart, float randEnd);
	AbstractNeuron* addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Merge this network with another one (The neurons of the otherNetwork will be removed from it)
	void mergeWith(LayeredNetwork& otherNetwork);	 

	void copyWeightsFrom(LayeredNetwork& otherNetwork);
};

#endif