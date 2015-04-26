#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Includes
#include <vector>

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;

// This class contains all stuff needed to describe a NeuralNetwork
class NeuralNetwork 
{
private:
	AbstractNetworkTopology* networkTopology;
public:
	~NeuralNetwork();
	NeuralNetwork(AbstractNetworkTopology* networkTopology_);
	// Recalculates the activation of all neurons is the given ActivationOrder
	void refreshAllNeurons(AbstractActivationOrder &activationOrder);
	// Returns all output numbers of the network
	std::unique_ptr<std::vector<float>> getOutput();
	// Sets all input neurons to the given numbers
	void setInput(std::vector<float> &inputVector);
	AbstractNetworkTopology* getNetworkTopology();
};

#endif