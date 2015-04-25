#pragma once

#ifndef _SAMEFUNCTIONSNEURONFACTORY_H_
#define _SAMEFUNCTIONSNEURONFACTORY_H_

// Includes
#include "AbstractNeuronFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class ActivationFunction;
class InputFunction;
class OutputFunction;

// This is the standard neuron factory, where every neuron has the same functions
class SameFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	ActivationFunction* activationFunction;
	InputFunction* inputFunction;
	OutputFunction* outputFunction;
public:	
	~SameFunctionsNeuronFactory();
	SameFunctionsNeuronFactory(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
};

#endif