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
	void setInput(std::vector<float>* inputVector);
public:
	NeuralNetwork(AbstractNetworkTopology* networkTopology_);
	// Calculates from the given input and activation order the output from neural network (If a not-NULL output value map or a netInput value map is given, the method will fill them)
	std::unique_ptr<NeuralNetworkIO<float>> calculate(NeuralNetworkIO<float>& input, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = 0, std::vector<std::map<AbstractNeuron*, float>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, float>>* netInputValuesInTime = NULL);
	AbstractNetworkTopology* getNetworkTopology();
};

#endif