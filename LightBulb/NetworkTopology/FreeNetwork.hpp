#pragma once

#ifndef _FREENETWORK_H_
#define _FREENETWORK_H_

// Libary includes
#include <vector>

// Includes
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\BiasNeuron.hpp"
#include "NetworkTopology\RecurrentNetworkInterface.hpp"

// Forward declarations
class AbstractNeuronFactory;
class FreeNetworkTopologyDrawer;

// This struct contains all options needed to build a FreeNetwork
struct FreeNetworkOptions
{	
	// Specifies the neuron factory
	AbstractNeuronFactory* neuronFactory;
	// Enables the use of a bias neuron
	bool useBiasNeuron;
	// Sets the total neuron count
	unsigned int neuronCount;
	// Enables real input neurons
	bool realInputNeurons;
	// Sets the input neurons count (only if the network should use real input neurons)
	unsigned int inputNeuronCount;
	// Enables self referencing edges
	bool selfReferencingEdges;
	// Specifies the indices of the input neurons (only needed if the network should not use real input neurons)
	std::vector<unsigned int> inputNeuronsIndices;
	// Specifies the indices of the output neurons
	std::vector<unsigned int> outputNeuronsIndices;
	FreeNetworkOptions();
	~FreeNetworkOptions();
	FreeNetworkOptions(const FreeNetworkOptions &obj);
};


// A free network can have any kind of structure. There are no rules.
class FreeNetwork : public AbstractNetworkTopology, public RecurrentNetworkInterface
{
	friend FreeNetworkTopologyDrawer;
protected:
	std::unique_ptr<FreeNetworkOptions> options;
	// Holds all neurons
	std::vector<StandardNeuron*> neurons;
	// Holds all input neurons
	std::vector<AbstractNeuron*> inputNeurons;
	// Holds all output neurons
	std::vector<StandardNeuron*> outputNeurons;
	// Holds the bias neurons
	BiasNeuron biasNeuron;
	// Builds the network from the given options
	void buildNetwork();	
public:
	~FreeNetwork();
	FreeNetwork(FreeNetworkOptions &options_);	
	FreeNetwork();	
	// Returns all InputNeurons 
	std::vector<AbstractNeuron*>* getInputNeurons();
	// Returns all OutputNeurons 
	std::vector<StandardNeuron*>* getOutputNeurons();
	// Returns all Neurons
	std::vector<std::vector<StandardNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(double randStart, double randEnd);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Puts all current neuron outputs into the given map
	void getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs);
	// Puts all current neuron net inputs into the given map
	void getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs);
	// Adds a neuron to the network
	AbstractNeuron* addNeuron(bool refreshNeuronCounters, bool inputNeuron = false);
	// Inherited:
	std::unique_ptr<LayeredNetwork> unfold(int instanceCount);
	BiasNeuron* getBiasNeuron();
};

#endif