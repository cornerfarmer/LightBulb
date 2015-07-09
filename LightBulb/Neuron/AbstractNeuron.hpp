#pragma once

#ifndef _ABSTRACTNEURON_H_
#define _ABSTRACTNEURON_H_

// Includes
#include <list>
#include <map>

// Forward declarations
class Edge;
class StandardNeuron;
class AbstractNeuron;

// Every neuron always has a activation and can have multiple efferent edges
class AbstractNeuron
{
protected:
	// Holds the activation
	double activation;
	// Holds all efferent edges
	std::list<Edge*> efferentEdges;
public:	
	virtual ~AbstractNeuron();
	AbstractNeuron();
	// Add a new efferent Edge which directs to the given neuron
	void addNextNeuron(StandardNeuron* newNextNeuron, double weight);
	void addNextNeuron(Edge* newEdge);
	// Returns the current activation of the neuron
	double getActivation();
	// Recalculate the activation of the neuron
	virtual void refreshActivation() = 0;
	// Recalculate the netInput of the neuron
	virtual void refreshNetInput(std::map<AbstractNeuron*, double>* neuronOutputCache = NULL) = 0;
	// Returns all efferent edges
	std::list<Edge*>* getEfferentEdges();
	// Resets the activation of the neuron
	virtual void resetActivation();
	// Remove a efferent Edge
	void removeEfferentEdge(Edge* edgeToRemove);
};

#endif