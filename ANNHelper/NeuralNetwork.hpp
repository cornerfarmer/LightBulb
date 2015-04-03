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
	void refreshAllNeurons(ActivationOrder &activationOrder);
	std::vector<float>* getOutput();
	void setInput(std::vector<float> &inputVector);
};

#endif