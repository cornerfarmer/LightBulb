#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronDescription/AbstractNeuronDescriptionFactory.hpp"

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
	template <class Archive>
	friend void serialize(Archive& archive, DifferentNeuronDescriptionFactory& descriptionFactory);
private:
	// Inner neurons
	std::unique_ptr<NeuronDescription> innerNeuronDescription;
	// Output neurons
	std::unique_ptr<NeuronDescription> outputNeuronDescription;
public:	
	DifferentNeuronDescriptionFactory(NeuronDescription* innerNeuronDescription_, NeuronDescription* outputNeuronDescription_);
	DifferentNeuronDescriptionFactory(const DifferentNeuronDescriptionFactory &obj);
	// Inherited:
	NeuronDescription* createInnerNeuronDescription() override;
	NeuronDescription* createOutputNeuronDescription() override;
	AbstractNeuronDescriptionFactory* getCopy() override;
	AbstractActivationFunction* getOutputActivationFunction() override;
	AbstractActivationFunction* getInnerActivationFunction() override;
};

#include "IO/DifferentNeuronDescriptionFactoryIO.hpp"

#endif