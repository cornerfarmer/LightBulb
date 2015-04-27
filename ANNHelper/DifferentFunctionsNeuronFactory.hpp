#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Library Includes
#include <memory>

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
	std::unique_ptr<AbstractActivationFunction> activationFunctionInnerNeuron;
	std::unique_ptr<AbstractInputFunction> inputFunctionInnerNeuron;
	std::unique_ptr<AbstractOutputFunction> outputFunctionInnerNeuron;
	// Functions for output neurons
	std::unique_ptr<AbstractActivationFunction> activationFunctionOutputNeuron;
	std::unique_ptr<AbstractInputFunction> inputFunctionOutputNeuron;
	std::unique_ptr<AbstractOutputFunction> outputFunctionOutputNeuron;
public:	
	DifferentFunctionsNeuronFactory(AbstractInputFunction* inputFunctionInnerNeuron_, AbstractActivationFunction* activationFunctionInnerNeuron_, AbstractOutputFunction* outputFunctionInnerNeuron_, AbstractInputFunction* inputFunctionOutputNeuron_, AbstractActivationFunction* activationFunctionOutputNeuron_, AbstractOutputFunction* outputFunctionOutputNeuron_);
	DifferentFunctionsNeuronFactory(const DifferentFunctionsNeuronFactory &obj);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
	AbstractNeuronFactory* getCopy();
};

#endif