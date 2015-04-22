#pragma once

#ifndef _NETWORKTOPOLOGY_H_
#define _NETWORKTOPOLOGY_H_

// Includes
#include <vector>

// Forward declarations
class InputNeuron;
class Neuron;

// A NetworkTopology is used to describe the structure of a NeuralNetwork
class NetworkTopology
{
private:
public:	
	virtual ~NetworkTopology() = 0;
	// Returns all InputNeurons in the NeuralNetwork
	virtual std::vector<Neuron*>* getInputNeurons() = 0;
	// Returns all OutputNeurons in the NeuralNetwork
	virtual std::vector<Neuron*>* getOutputNeurons() = 0;
	// Set all weights to new random values between randStart and randEnd
	virtual void randomizeWeights(float randStart, float randEnd) = 0;
	// Returns all Neurons
	virtual std::vector<std::vector<Neuron*>>* getNeurons() = 0;
};

#endif
