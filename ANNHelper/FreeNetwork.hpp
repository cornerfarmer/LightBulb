#pragma once

#ifndef _FREENETWORK_H_
#define _FREENETWORK_H_

// Libary includes
#include <vector>

// Includes
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "BiasNeuron.hpp"

// Forward declarations
class AbstractNeuronFactory;

// This struct contains all options needed to build a FreeNetwork
struct FreeNetworkOptions
{	
	AbstractNeuronFactory* neuronFactory;
	bool useBiasNeuron;
	unsigned int neuronCount;
	unsigned int inputNeuronCount;
	unsigned int outputNeuronCount;
	FreeNetworkOptions();
	~FreeNetworkOptions();
	FreeNetworkOptions(const FreeNetworkOptions &obj);
};


// 
class FreeNetwork : public AbstractNetworkTopology
{
protected:
	std::unique_ptr<FreeNetworkOptions> options;
	std::vector<StandardNeuron*> neurons;
	std::vector<StandardNeuron*> inputNeurons;
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
	std::vector<AbstractNeuron*>* getOutputNeurons();
	// Returns all Neurons
	std::vector<std::vector<AbstractNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(float randStart, float randEnd);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Merge this network with another one (The neurons of the otherNetwork will be removed from it)
	void mergeWith(LayeredNetwork& otherNetwork);	 
	// Copies the weight from all matching edges from the other network into the current one
	void copyWeightsFrom(LayeredNetwork& otherNetwork);
	// Puts all current neuron outputs into the given map
	void getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs);
	// Puts all current neuron net inputs into the given map
	void getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs);
};

#endif