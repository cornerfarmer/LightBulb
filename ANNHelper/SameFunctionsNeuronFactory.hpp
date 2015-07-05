#pragma once

#ifndef _SAMEFUNCTIONSNEURONFACTORY_H_
#define _SAMEFUNCTIONSNEURONFACTORY_H_

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

// This is the standard neuron factory, where every neuron has the same functions
class SameFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	std::unique_ptr<AbstractActivationFunction> activationFunction;
	std::unique_ptr<AbstractInputFunction> inputFunction;
	std::unique_ptr<AbstractOutputFunction> outputFunction;
	std::unique_ptr<AbstractThreshold> threshold;
public:	
	SameFunctionsNeuronFactory(AbstractThreshold* threshold, AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_);
	SameFunctionsNeuronFactory(const SameFunctionsNeuronFactory &obj);
	// Inherited:
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
	AbstractNeuronFactory* getCopy();
};

#endif