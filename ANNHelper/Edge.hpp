#pragma once

#ifndef _EDGE_H_
#define _EDGE_H_

// Forward declarations
class Neuron;
class StandardNeuron;

// A Edge connects two Neurons
class Edge
{
private:
	float weight;
	Neuron* prevNeuron;
	StandardNeuron* nextNeuron;
public:
	Edge(Neuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_);	
};

#endif