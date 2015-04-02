#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include <vector>

#include "NetworkTopology.hpp"
#include "ActivationOrder.hpp"

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