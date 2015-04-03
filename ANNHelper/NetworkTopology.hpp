#pragma once

#ifndef _NETWORKTOPOLOGY_H_
#define _NETWORKTOPOLOGY_H_

// Includes
#include <list>

// Forward declarations
class InputNeuron;
class Neuron;

// A NetworkTopology is used to describe the structure of a NeuralNetwork
class NetworkTopology
{
private:
public:	
	virtual ~NetworkTopology() = 0;
	std::list<InputNeuron>* getInputNeurons();
	std::list<Neuron>* getOutputNeurons();
};

#endif
