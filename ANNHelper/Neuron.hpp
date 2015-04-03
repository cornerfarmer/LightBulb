#pragma once

#ifndef _NEURON_H_
#define _NEURON_H_

#include <list>

class Edge;

class Neuron
{
protected:
	float activation;
	std::list<Edge*> efferentEdges;
public:	
	~Neuron();
	Neuron();
	void addNextNeuron(Neuron* newNextNeuron, float weight);
	float getActivation();
	virtual void refreshActivation() = 0;
};

#endif