#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronFactory/AbstractNeuronDescriptionFactory.hpp"

// Forward declarations
class InputNeuron;
class StandardNeuron;
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;
class AbstractThreshold;

// This factory makes it possible to use different functions for inner and output neurons
class DifferentNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
{
private:
	// Inner neurons
	std::unique_ptr<NeuronDescription> innerNeuronDescription;
	// Output neurons
	std::unique_ptr<NeuronDescription> outputNeuronDescription;
public:	
	DifferentNeuronDescriptionFactory(NeuronDescription* innerNeuronDescription_, NeuronDescription* outputNeuronDescription_);
	DifferentNeuronDescriptionFactory(const DifferentNeuronDescriptionFactory &obj);
	// Inherited:
	NeuronDescription* createInnerNeuronDescription();
	NeuronDescription* createOutputNeuronDescription();
	AbstractNeuronDescriptionFactory* getCopy();
	AbstractActivationFunction* getOutputActivationFunction();
	AbstractActivationFunction* getInnerActivationFunction();
};

#endif