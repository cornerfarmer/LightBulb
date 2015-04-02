#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include "NetworkTopology.hpp"
#include "ActivationOrder.hpp"

class NeuralNetwork 
{
private:
	NetworkTopology* networkTopology;
public:
	NeuralNetwork();	 
	NeuralNetwork(NetworkTopology* networkTopology_);
	refreshAllNeurons(ActivationOrder &activationOrder);
	float[] getOutput();
	setInput(int inputVector[]);
};

#endif