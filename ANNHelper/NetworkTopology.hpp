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
	// Returns all InputNeurons in the NeuralNetwork
	std::list<InputNeuron>* getInputNeurons();
	// Returns all OutputNeurons in the NeuralNetwork
	std::list<Neuron>* getOutputNeurons();
};

#endif
