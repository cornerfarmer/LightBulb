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
class AbstractThreshold;

// This factory makes it possible to use different functions for inner and output neurons
class DifferentFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	// Inner neurons
	std::unique_ptr<AbstractThreshold> thresholdInnerNeuron;
	std::unique_ptr<AbstractActivationFunction> activationFunctionInnerNeuron;
	std::unique_ptr<AbstractInputFunction> inputFunctionInnerNeuron;
	std::unique_ptr<AbstractOutputFunction> outputFunctionInnerNeuron;
	// Output neurons
	std::unique_ptr<AbstractThreshold> thresholdOutputNeuron;
	std::unique_ptr<AbstractActivationFunction> activationFunctionOutputNeuron;
	std::unique_ptr<AbstractInputFunction> inputFunctionOutputNeuron;
	std::unique_ptr<AbstractOutputFunction> outputFunctionOutputNeuron;
public:	
	DifferentFunctionsNeuronFactory(AbstractThreshold* thresholdInnerNeuron_, AbstractInputFunction* inputFunctionInnerNeuron_, AbstractActivationFunction* activationFunctionInnerNeuron_, AbstractOutputFunction* outputFunctionInnerNeuron_, AbstractThreshold* thresholdOutputNeuron_, AbstractInputFunction* inputFunctionOutputNeuron_, AbstractActivationFunction* activationFunctionOutputNeuron_, AbstractOutputFunction* outputFunctionOutputNeuron_);
	DifferentFunctionsNeuronFactory(const DifferentFunctionsNeuronFactory &obj);
	// Inherited:
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
	AbstractNeuronFactory* getCopy();
};

#endif