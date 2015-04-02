#pragma once

#ifndef _NEURON_H_
#define _NEURON_H_

#include <list>

#include "Edge.hpp"
#include "Neuron.hpp"

class Neuron
{
protected:
	float activation;
	std::list<Edge*> efferentEdges;
public:	
	Neuron();
	void addNextNeuron(Neuron* newNextNeuron, float weight);
	float getActivation();
	virtual void refreshActivation() = 0;
};

#endif