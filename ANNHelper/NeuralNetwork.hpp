#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>

// Includes
#include "NeuralNetworkIO.hpp"

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// This class contains all stuff needed to describe a NeuralNetwork
class NeuralNetwork 
{
private:
	std::unique_ptr<AbstractNetworkTopology> networkTopology;
	// Returns all output numbers of the network
	std::unique_ptr<std::vector<float>> getOutput();
	// Sets all input neurons to the given numbers
	void setInput(std::vector<float> &inputVector);
public:
	NeuralNetwork(AbstractNetworkTopology* networkTopology_);
	std::unique_ptr<NeuralNetworkIO> calculate(NeuralNetworkIO& input, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	AbstractNetworkTopology* getNetworkTopology();
};

#endif