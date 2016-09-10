#pragma once

#ifndef _NEURONDESCRIPTION_H_
#define _NEURONDESCRIPTION_H_

// Includes
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"

// Library includes
#include <memory>

namespace LightBulb
{
	// Forward declarations

	class NeuronDescription
	{
		template <class Archive>
		friend void serialize(Archive& archive, NeuronDescription& neuronDescription);
	private:
		std::unique_ptr<AbstractInputFunction> inputFunction;
		std::unique_ptr<AbstractActivationFunction> activationFunction;
	public:
		NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_);
		NeuronDescription() = default;
		NeuronDescription* getCopy();
		AbstractInputFunction* getInputFunction();
		virtual AbstractActivationFunction* getActivationFunction();
	};
}

#include "IO/NeuronDescriptionIO.hpp"

#endif