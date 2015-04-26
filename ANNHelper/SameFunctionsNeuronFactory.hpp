#pragma once

#ifndef _SAMEFUNCTIONSNEURONFACTORY_H_
#define _SAMEFUNCTIONSNEURONFACTORY_H_

// Includes
#include "AbstractNeuronFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;

// This is the standard neuron factory, where every neuron has the same functions
class SameFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	AbstractActivationFunction* activationFunction;
	AbstractInputFunction* inputFunction;
	AbstractOutputFunction* outputFunction;
public:	
	~SameFunctionsNeuronFactory();
	SameFunctionsNeuronFactory(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
};

#endif