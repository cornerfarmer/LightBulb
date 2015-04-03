#pragma once

#ifndef _NETWORKTOPOLOGY_H_
#define _NETWORKTOPOLOGY_H_

#include <list>

class InputNeuron;
class Neuron;

class NetworkTopology
{
private:
public:	
	virtual ~NetworkTopology() = 0;
	std::list<InputNeuron>* getInputNeurons();
	std::list<Neuron>* getOutputNeurons();
};

#endif
