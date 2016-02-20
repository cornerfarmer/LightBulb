#pragma once

#ifndef _ABSTRACTNEURALNETWORK_H_
#define _ABSTRACTNEURALNETWORK_H_

// Libraray includes
#include <vector>
#include <map>

// Includes

// Forward declarations
class AbstractNetworkTopology;
class AbstractActivationOrder;
class AbstractNeuron;

// This class contains all stuff needed to describe a NeuralNetwork
class AbstractNeuralNetwork 
{
private:
public:
	virtual ~AbstractNeuralNetwork() {};
	// Calculates from the given input and activation order the output from neural network (If a not-NULL output value map or a netInput value map is given, the method will fill them)
	virtual void calculate(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, AbstractActivationOrder &activationOrder, int startTime = 0, int timeStepCount = -1, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = NULL, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = NULL, bool resetActivations = true) = 0;
	virtual void calculate(std::vector<double>& input, std::vector<double>& output, AbstractActivationOrder &activationOrder, bool resetActivations = true) = 0;
	virtual AbstractNetworkTopology* getNetworkTopology() = 0;
};

#endif
