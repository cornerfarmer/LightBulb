#pragma once

#ifndef _ABSTRACTNEURONDESCRIPTIONFACTORY_H_
#define _ABSTRACTNEURONDESCRIPTIONFACTORY_H_

// Forward declarations
class NeuronDescription;

// This is a basic schema for all neuron factories
class AbstractNeuronDescriptionFactory
{
private:
public:	
	virtual ~AbstractNeuronDescriptionFactory() {}
	// Create a new inner neuron
	virtual NeuronDescription* createInnerNeuronDescription() = 0;
	// Create a new output neuron
	virtual NeuronDescription* createOutputNeuronDescription() = 0;
	// Get a copy of the factory
	virtual AbstractNeuronDescriptionFactory* getCopy() = 0;
};

#endif