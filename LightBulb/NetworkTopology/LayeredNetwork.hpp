#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

// Libary includes
#include <vector>
#include <memory>

// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/BiasNeuron.hpp"

// Forward declarations
class AbstractNeuronFactory;

// This struct contains all options needed to build a LayeredNetwork
struct LayeredNetworkOptions
{	
	// Specifies the neuron factory
	AbstractNeuronFactory* neuronFactory;
	// Enables shourtcut edges
	bool enableShortcuts;
	// Enables a bias neuron
	bool useBiasNeuron;
	// Specifies the neuron count of every layer
	std::vector<unsigned int> neuronsPerLayerCount;
	// Specifies which neurons of the last layer will be used as output neurons (if empty, the whole last layer will be used)
	std::vector<unsigned int> outputNeuronsIndices;
	LayeredNetworkOptions();
	~LayeredNetworkOptions();
	LayeredNetworkOptions(const LayeredNetworkOptions &obj);
};

typedef struct LayeredNetworkOptions LayeredNetworkOptions_t;

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : public AbstractNetworkTopology
{
protected:
	std::unique_ptr<LayeredNetworkOptions_t> options;
	// Holds all neurons
	std::vector<std::vector<StandardNeuron*>> neurons;
	// Holds the bias neuron
	BiasNeuron biasNeuron;
	// Holds all output neurons
	std::vector<StandardNeuron*> outputNeurons;
	// Holds all input neurons
	std::vector<AbstractNeuron*> inputNeurons;
	// Builds the network from the given options
	void buildNetwork();	
	// Refreshes the neuronPerLayerCounters
	void refreshNeuronsPerLayerCounters();
	// Rebuilds the output neurons vector from the outputNeuronsIndices option
	void rebuildOutputNeurons();

public:
	~LayeredNetwork();
	LayeredNetwork(LayeredNetworkOptions_t &options_);	
	LayeredNetwork();	
	// Returns all InputNeurons (first layer)
	std::vector<AbstractNeuron*>* getInputNeurons();
	// Returns all OutputNeurons (last layer)
	std::vector<StandardNeuron*>* getOutputNeurons();
	// Calculates the layer count
	int getLayerCount();
	// Returns all Neurons
	std::vector<std::vector<StandardNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(double randStart, double randEnd);
	// Adds a new neuron into the specified layer
	AbstractNeuron* addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer);
	// Removes the neuron with given index from a layer
	void removeNeuronFromLayer(int layerIndex, int neuronIndex);
	// Removes the givem neuron from a layer
	void removeNeuronFromLayer(int layerIndex, AbstractNeuron* neuronToRemove);
	// Adds a new layer
	void addNewLayer(int layerIndex, int initialNeuronCount);
	// Adds a given neuron to a layer
	void addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Merge this network with another one (The neurons of the otherNetwork will be removed from it)
	void mergeWith(LayeredNetwork& otherNetwork);	 
	// Merge this network with another one
	virtual void horizontalMergeWith(LayeredNetwork& otherNetwork);
	// Returns a map which holds for every edge the information if it is recurrent or not
	virtual std::unique_ptr<std::map<Edge*, bool>> getNonRecurrentEdges();
	// Puts all current neuron outputs into the given map
	void getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs);
	// Puts all current neuron net inputs into the given map
	void getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs);
	// Returns the bias neuron
	BiasNeuron* getBiasNeuron();
};

#endif
