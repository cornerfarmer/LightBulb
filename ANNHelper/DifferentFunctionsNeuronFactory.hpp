#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Includes
#include "AbstractNeuronFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class ActivationFunction;
class InputFunction;
class OutputFunction;

// This factory makes it possible to use different functions for inner and output neurons
class DifferentFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	// Functions for inner neurons
	ActivationFunction* activationFunctionInnerNeuron;
	InputFunction* inputFunctionInnerNeuron;
	OutputFunction* outputFunctionInnerNeuron;
	// Functions for output neurons
	ActivationFunction* activationFunctionOutputNeuron;
	InputFunction* inputFunctionOutputNeuron;
	OutputFunction* outputFunctionOutputNeuron;
public:	
	~DifferentFunctionsNeuronFactory();
	DifferentFunctionsNeuronFactory(InputFunction* inputFunctionInnerNeuron_, ActivationFunction* activationFunctionInnerNeuron_, OutputFunction* outputFunctionInnerNeuron_, InputFunction* inputFunctionOutputNeuron_, ActivationFunction* activationFunctionOutputNeuron_, OutputFunction* outputFunctionOutputNeuron_);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
};

#endif