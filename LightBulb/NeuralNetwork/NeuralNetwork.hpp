#pragma once

#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>

// Includes
#include "NeuralNetwork\NeuralNetworkIO.hpp"

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
	void getOutput(std::vector<std::pair<bool, double>> &outputVector);
	// Sets all input neurons to the given numbers
	void setInput(std::vector<std::pair<bool, double>>* inputVector);
public:
	NeuralNetwork(AbstractNetworkTopology* networkTopology_);	
	// Calculates from the given input and activation order the output from neural network (If a not-NULL output value map or a netInput value map is given, the method will fill them)
	std::unique_ptr<NeuralNetworkIO<double>> calculate(NeuralNetworkIO<double>& input, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = NULL);
	AbstractNetworkTopology* getNetworkTopology();
};

#endif