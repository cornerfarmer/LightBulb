#pragma once

#ifndef _STANDARDNEURON_H_
#define _STANDARDNEURON_H_

// Includes
#include "Neuron\AbstractNeuron.hpp"

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
	float additionalInput;
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
	// Calculates a new activation with the help of its activation- and outputFunction
	void refreshActivation();
	// Calculates a new netInput with the help of its inputFunction
	void refreshNetInput(std::map<AbstractNeuron*, float>* neuronOutputCache = NULL);
	// Calculates the value of the activation function derivation 
	float executeDerivationOnActivationFunction(float input);
	// Returns the afferent edges
	std::list<Edge*>* getAfferentEdges();
	// Returs the netInput
	float getNetInput();
	// Returns the activation function
	AbstractActivationFunction* getActivationFunction();
	// Returns the threshold
	AbstractThreshold* getThreshold();
	// Sets the additional input
	void setAdditionalInput(float newAdditionalInput);
	// Sets the current activation
	void injectActivation(float newActivation);
};

#endif