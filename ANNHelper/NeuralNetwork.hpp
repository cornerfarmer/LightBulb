#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include <vector>

class NetworkTopology;
class ActivationOrder;

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