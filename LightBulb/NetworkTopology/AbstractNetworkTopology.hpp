#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOGY_H_
#define _ABSTRACTNETWORKTOPOLOGY_H_

// Library includes
#include <vector>
#include <map>

// Forward declarations
class InputNeuron;
class AbstractNeuron;
class StandardNeuron;
class Edge;
class BiasNeuron;

// A NetworkTopology is used to describe the structure of a NeuralNetwork
class AbstractNetworkTopology
{
private:
public:	
	virtual ~AbstractNetworkTopology() {};
	// Returns all InputNeurons in the NeuralNetwork
	virtual std::vector<AbstractNeuron*>* getInputNeurons() = 0;
	// Returns all OutputNeurons in the NeuralNetwork
	virtual std::vector<StandardNeuron*>* getOutputNeurons() = 0;
	// Set all weights to new random values between randStart and randEnd
	virtual void randomizeWeights(double randStart, double randEnd) = 0;
	// Returns all Neurons
	virtual std::vector<std::vector<StandardNeuron*>>* getNeurons() = 0;
	// Calculates the Edge count
	virtual int getEdgeCount() = 0;
	// Reset the activation of all neurons
	virtual void resetActivation() = 0;
	// Puts all current neuronOutputValues into the given map
	virtual void getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs) = 0;
	// Puts all current neuronNetInputValues into the given map
	virtual void getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs) = 0;
	// Copies the weight from all matching edges from the other network into the current one
	void copyWeightsFrom(AbstractNetworkTopology& otherNetwork);
	// Returns the biasNeuron
	virtual BiasNeuron* getBiasNeuron() = 0;
};

#endif