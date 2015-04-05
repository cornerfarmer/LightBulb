#pragma once

#ifndef _STANDARDNEURON_H_
#define _STANDARDNEURON_H_

// Includes
#include "Neuron.hpp"

// Forward declarations
class ActivationFunction;
class InputFunction;
class OutputFunction;
class Edge;

// All neurons except of InputNeurons are StandardNeurons.
// They have at least one afferent edge and 0..* efferent edges.
class StandardNeuron : public Neuron
{
private:
	float threshold;
	float netInput;
	InputFunction* inputFunction;
	ActivationFunction* activationFunction;
	OutputFunction* outputFunction;
	std::list<Edge*> afferentEdges;
public:
	~StandardNeuron();
	StandardNeuron(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_);
	// Add a new afferent Edge directing to the given neuron
	void addPrevNeuron(Neuron* newPrevNeuron, float weight);
	void addPrevNeuron(Edge* newEdge);
	// Calculates a new activation with the help of its input-, activation- and outputFunction
	void refreshActivation();
	// Calculates the value of the activation function derivation 
	float executeDerivationOnActivationFunction(float input);
	std::list<Edge*>* getAfferentEdges();
	float getNetInput();
};

#endif