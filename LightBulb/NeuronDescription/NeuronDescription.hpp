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
	/**
	 * \brief Contains all neuron specific information. 
	 */
	class NeuronDescription
	{
		template <class Archive>
		friend void serialize(Archive& archive, NeuronDescription& neuronDescription);
	private:
		/**
		 * \brief The input function of the neuron.
		 */
		std::unique_ptr<AbstractInputFunction> inputFunction;
		/**
		 * \brief The activation function of the neuron.
		 */
		std::unique_ptr<AbstractActivationFunction> activationFunction;
	public:
		/**
		 * \brief Creates a neuron description.
		 * \param inputFunction_ The input function of the neuron.
		 * \param activationFunction_ The activation function of the neuron.
		 */
		NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_);
		/**
		 * \brief Creates a neuron description.
		 */
		NeuronDescription() = default;
		/**
		 * \brief Clones the neuron description.
		 * \return The clone.
		 */
		NeuronDescription* getCopy();
		/**
		 * \brief Returns the input function of the neuron.
		 * \return The input function.
		 */
		AbstractInputFunction* getInputFunction();
		/**
		 * \brief Returns the activation function of the neuron.
		 * \return The activation function.
		 */
		virtual AbstractActivationFunction* getActivationFunction();
	};
}

#include "IO/NeuronDescriptionIO.hpp"

#endif