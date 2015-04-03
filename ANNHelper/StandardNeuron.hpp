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
class StandardNeuron : Neuron
{
private:
	float threshold;
	InputFunction* inputFunction;
	ActivationFunction* activationFunction;
	OutputFunction* outputFunction;
	std::list<Edge*> afferentEdges;
public:
	~StandardNeuron();
	StandardNeuron();
	StandardNeuron(InputFunction* inputFunction, ActivationFunction* activationFunction, OutputFunction* outputFunction);
	void addPrevNeuron(Neuron* newPrevNeuron, float weight);
	void refreshActivation();
};

#endif