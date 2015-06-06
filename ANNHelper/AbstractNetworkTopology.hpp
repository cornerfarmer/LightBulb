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
	virtual void randomizeWeights(float randStart, float randEnd) = 0;
	// Returns all Neurons
	virtual std::vector<std::vector<StandardNeuron*>>* getNeurons() = 0;
	// Calculates the Edge count
	virtual int getEdgeCount() = 0;

	virtual void resetActivation() = 0;

	virtual void getAllNeuronOutputs(std::map<AbstractNeuron*, float>& neuronOutputs) = 0;
	
	virtual void getAllNeuronNetInputs(std::map<AbstractNeuron*, float>& neuronNetInputs) = 0;
	// Copies the weight from all matching edges from the other network into the current one
	void copyWeightsFrom(AbstractNetworkTopology& otherNetwork);
};

#endif