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

// This is the standard neuron factory, where every neuron has the same functions
class SameFunctionsNeuronFactory : public AbstractNeuronFactory
{
private:
	std::unique_ptr<AbstractActivationFunction> activationFunction;
	std::unique_ptr<AbstractInputFunction> inputFunction;
	std::unique_ptr<AbstractOutputFunction> outputFunction;
public:	
	SameFunctionsNeuronFactory(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_);
	SameFunctionsNeuronFactory(const SameFunctionsNeuronFactory &obj);
	InputNeuron* createInputNeuron();
	StandardNeuron* createInnerNeuron();
	StandardNeuron* createOutputNeuron();
	AbstractNeuronFactory* getCopy();
};

#endif