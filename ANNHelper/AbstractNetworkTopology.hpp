#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOGY_H_
#define _ABSTRACTNETWORKTOPOLOGY_H_

// Includes
#include <vector>

// Forward declarations
class InputNeuron;
class AbstractNeuron;

// A NetworkTopology is used to describe the structure of a NeuralNetwork
class AbstractNetworkTopology
{
private:
public:	
	virtual ~AbstractNetworkTopology() {};
	// Returns all InputNeurons in the NeuralNetwork
	virtual std::vector<AbstractNeuron*>* getInputNeurons() = 0;
	// Returns all OutputNeurons in the NeuralNetwork
	virtual std::vector<AbstractNeuron*>* getOutputNeurons() = 0;
	// Set all weights to new random values between randStart and randEnd
	virtual void randomizeWeights(float randStart, float randEnd) = 0;
	// Returns all Neurons
	virtual std::vector<std::vector<AbstractNeuron*>>* getNeurons() = 0;
	// Add a new Neuron in the selected Layer
	virtual AbstractNeuron* addNeuronIntoLayer(int layerIndex) = 0;
};

#endif
