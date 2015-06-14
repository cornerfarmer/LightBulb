#pragma once

#ifndef _FREENETWORK_H_
#define _FREENETWORK_H_

// Libary includes
#include <vector>

// Includes
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "BiasNeuron.hpp"
#include "RecurrentNetworkInterface.hpp"

// Forward declarations
class AbstractNeuronFactory;

// This struct contains all options needed to build a FreeNetwork
struct FreeNetworkOptions
{	
	AbstractNeuronFactory* neuronFactory;
	bool useBiasNeuron;
	unsigned int neuronCount;
	bool realInputNeurons;
	unsigned int inputNeuronCount;
	std::vector<unsigned int> inputNeuronsIndices;
	std::vector<unsigned int> outputNeuronsIndices;
	FreeNetworkOptions();
	~FreeNetworkOptions();
	FreeNetworkOptions(const FreeNetworkOptions &obj);
};


// 
class FreeNetwork : public AbstractNetworkTopology, public RecurrentNetworkInterface
{
protected:
	std::unique_ptr<FreeNetworkOptions> options;
	std::vector<StandardNeuron*> neurons;
	std::vector<AbstractNeuron*> inputNeurons;
	std::vector<StandardNeuron*> outputNeurons;
	BiasNeuron biasNeuron;
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
	void randomizeWeights(float randStart, float randEnd);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Puts all current neuron outputs into the given map
	void getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs);
	// Puts all current neuron net inputs into the given map
	void getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs);

	AbstractNeuron* addNeuron(bool refreshNeuronCounters, bool inputNeuron = false);
	// Inherited:
	std::unique_ptr<LayeredNetwork> unfold(int instanceCount);
	BiasNeuron* getBiasNeuron();
};

#endif