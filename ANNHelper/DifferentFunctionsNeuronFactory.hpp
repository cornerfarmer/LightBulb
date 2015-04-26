#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Includes
#include "AbstractNeuronFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;

// This factory makes it possible to use different functions for inner and output neurons
class DifferentFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	// Functions for inner neurons
	AbstractActivationFunction* activationFunctionInnerNeuron;
	AbstractInputFunction* inputFunctionInnerNeuron;
	AbstractOutputFunction* outputFunctionInnerNeuron;
	// Functions for output neurons
	AbstractActivationFunction* activationFunctionOutputNeuron;
	AbstractInputFunction* inputFunctionOutputNeuron;
	AbstractOutputFunction* outputFunctionOutputNeuron;
public:	
	~DifferentFunctionsNeuronFactory();
	DifferentFunctionsNeuronFactory(AbstractInputFunction* inputFunctionInnerNeuron_, AbstractActivationFunction* activationFunctionInnerNeuron_, AbstractOutputFunction* outputFunctionInnerNeuron_, AbstractInputFunction* inputFunctionOutputNeuron_, AbstractActivationFunction* activationFunctionOutputNeuron_, AbstractOutputFunction* outputFunctionOutputNeuron_);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
};

#endif