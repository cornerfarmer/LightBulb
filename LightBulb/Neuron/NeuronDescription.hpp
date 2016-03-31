#pragma once

#ifndef _NEURONDESCRIPTION_H_
#define _NEURONDESCRIPTION_H_

// Includes
#include "Function/AbstractInputFunction.hpp"
#include "Function/AbstractActivationFunction.hpp"

// Forward declarations

// Library includes
#include <memory>

class NeuronDescription
{
	template <class Archive>
	friend void serialize(Archive& archive, NeuronDescription& neuronDescription);
private:
	std::unique_ptr<AbstractInputFunction> inputFunction;
	std::unique_ptr<AbstractActivationFunction> activationFunction;
public:
	NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_);
	NeuronDescription* getCopy();
	AbstractInputFunction* getInputFunction();
	AbstractActivationFunction* getActivationFunction();
};

#endif