#pragma once

#ifndef _ABSTRACTNEURONFACTORY_H_
#define _ABSTRACTNEURONFACTORY_H_

// Forward declarations
class InputNeuron;
class StandardNeuron;

// This is a basic schema for all neuron factories
class AbstractNeuronFactory
{
private:
public:	
	virtual ~AbstractNeuronFactory() {}
	// Create a new input neuron
	virtual InputNeuron* createInputNeuron() = 0;
	// Create a new inner neuron
	virtual StandardNeuron* createInnerNeuron() = 0;
	// Create a new output neuron
	virtual StandardNeuron* createOutputNeuron() = 0;
};

#endif