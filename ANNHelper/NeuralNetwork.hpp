#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Includes
#include <vector>

// Forward declarations
class NetworkTopology;
class ActivationOrder;

// This class contains all stuff needed to describe a NeuralNetwork
class NeuralNetwork 
{
private:
	NetworkTopology* networkTopology;
public:
	~NeuralNetwork();
	NeuralNetwork();	 
	NeuralNetwork(NetworkTopology* networkTopology_);
	// Recalculates the activation of all neurons is the given ActivationOrder
	void refreshAllNeurons(ActivationOrder &activationOrder);
	// Returns all output numbers of the network
	std::vector<float>* getOutput();
	// Sets all input neurons to the given numbers
	void setInput(std::vector<float> &inputVector);
};

#endif