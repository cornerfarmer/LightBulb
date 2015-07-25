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

// Library includes
#include <vector>

// All neurons except of InputNeurons are StandardNeurons.
// They have at least one afferent edge and 0..* efferent edges.
class StandardNeuron : public AbstractNeuron
{
private:
	AbstractThreshold* threshold;
	double netInput;
	double additionalInput;
	AbstractInputFunction* inputFunction;
	AbstractActivationFunction* activationFunction;
	AbstractOutputFunction* outputFunction;
	std::list<Edge*> afferentEdges;
public:
	~StandardNeuron();
	StandardNeuron(AbstractThreshold* threshold_, AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_);
	// Add a new afferent Edge directing to the given neuron
	void addPrevNeuron(AbstractNeuron* newPrevNeuron, double weight);
	void addPrevNeuron(Edge* newEdge);
	// Remove a afferent Edge
	void removeAfferentEdge(Edge* edgeToRemove);
	// Calculates a new activation with the help of its activation- and outputFunction
	void refreshActivation();
	// Calculates a new netInput with the help of its inputFunction
	void refreshNetInput(std::map<AbstractNeuron*, double>* neuronOutputCache = NULL);
	// Calculates the value of the activation function derivation 
	double executeDerivationOnActivationFunction(double input);
	// Returns the afferent edges
	std::list<Edge*>* getAfferentEdges();
	// Returs the netInput
	double getNetInput();
	// Returns the activation function
	AbstractActivationFunction* getActivationFunction();
	// Returns the threshold
	AbstractThreshold* getThreshold();
	// Sets the additional input
	void setAdditionalInput(double newAdditionalInput);
	// Sets the current activation
	void injectActivation(double newActivation);

	std::vector<double> getAfferentWeightsVector();
};

#endif