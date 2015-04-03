#pragma once

#ifndef _NEURON_H_
#define _NEURON_H_

// Includes
#include <list>

// Forward declarations
class Edge;

// Every neuron always has a activation and can have multiple efferent edges
class Neuron
{
protected:
	float activation;
	std::list<Edge*> efferentEdges;
public:	
	~Neuron();
	Neuron();
	// Add a new efferent Edge which directs to the given neuron
	void addNextNeuron(Neuron* newNextNeuron, float weight);
	// Returns the current activation of the neuron
	float getActivation();
	// Recalculate the activation of the neuron
	virtual void refreshActivation() = 0;
};

#endif