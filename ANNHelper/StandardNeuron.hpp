#pragma once

#ifndef _STANDARDNEURON_H_
#define _STANDARDNEURON_H_

// Includes
#include "AbstractNeuron.hpp"

// Forward declarations
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;
class AbstractThreshold;
class Edge;

// All neurons except of InputNeurons are StandardNeurons.
// They have at least one afferent edge and 0..* efferent edges.
class StandardNeuron : public AbstractNeuron
{
private:
	AbstractThreshold* threshold;
	float netInput;
	AbstractInputFunction* inputFunction;
	AbstractActivationFunction* activationFunction;
	AbstractOutputFunction* outputFunction;
	std::list<Edge*> afferentEdges;
public:
	~StandardNeuron();
	StandardNeuron(AbstractThreshold* threshold_, AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_);
	// Add a new afferent Edge directing to the given neuron
	void addPrevNeuron(AbstractNeuron* newPrevNeuron, float weight);
	void addPrevNeuron(Edge* newEdge);
	// Remove a afferent Edge
	void removeAfferentEdge(Edge* edgeToRemove);
	// Calculates a new activation with the help of its input-, activation- and outputFunction
	void refreshActivation();
	// Calculates the value of the activation function derivation 
	float executeDerivationOnActivationFunction(float input);
	std::list<Edge*>* getAfferentEdges();
	float getNetInput();
	AbstractActivationFunction* getActivationFunction();
	AbstractThreshold* getThreshold();
};

#endif