#pragma once

#ifndef _EDGE_H_
#define _EDGE_H_

#include "Neuron.hpp"
#include "InputNeuron.hpp"

class Edge
{
private:
	float weight;
	Neuron* prevNeuron;
	InputNeuron* nextNeuron;
public:
	Edge();
	Edge(Neuron* prevNeuron_, InputNeuron* nextNeuron_, float weight_);	
};

#endif