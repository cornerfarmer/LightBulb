#pragma once

#ifndef _ABSTRACTNEURON_H_
#define _ABSTRACTNEURON_H_

// Includes
#include <vector>

// Forward declarations
class Edge;
class StandardNeuron;

// Every neuron always has a activation and can have multiple efferent edges
class AbstractNeuron
{
protected:
	float activation;
	std::vector<Edge*> efferentEdges;
public:	
	virtual ~AbstractNeuron();
	AbstractNeuron();
	// Add a new efferent Edge which directs to the given neuron
	void addNextNeuron(StandardNeuron* newNextNeuron, float weight);
	void addNextNeuron(Edge* newEdge);
	// Returns the current activation of the neuron
	float getActivation();
	// Recalculate the activation of the neuron
	virtual void refreshActivation() = 0;
	std::vector<Edge*>* getEfferentEdges();
};

#endif