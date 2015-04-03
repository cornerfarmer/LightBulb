#pragma once

#ifndef _EDGE_H_
#define _EDGE_H_

class Neuron;
class StandardNeuron;

class Edge
{
private:
	float weight;
	Neuron* prevNeuron;
	StandardNeuron* nextNeuron;
public:
	Edge();
	Edge(Neuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_);	
};

#endif