#pragma once

#ifndef _STANDARDNEURON_H_
#define _STANDARDNEURON_H_

#include "Neuron.hpp"
#include "ActivationFunction.hpp"
#include "InputFunction.hpp"
#include "OutputFunction.hpp"
#include "Edge.hpp"

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
};

#endif