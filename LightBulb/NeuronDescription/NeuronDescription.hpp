#pragma once

#ifndef _NEURONDESCRIPTION_H_
#define _NEURONDESCRIPTION_H_

// Includes
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <memory>

namespace LightBulb
{
	/**
	 * \brief Contains all neuron specific information. 
	 */
	class NeuronDescription : public virtual AbstractCloneable
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
		 * \brief Copy constructor.
		 * \param other Object to copy.
		 */
		NeuronDescription(const NeuronDescription& other);

		NeuronDescription& operator=(NeuronDescription other);

		friend void swap(NeuronDescription& lhs, NeuronDescription& rhs) noexcept;

		/**
		 * \brief Creates a neuron description.
		 */
		NeuronDescription() = default;
		/**
		 * \brief Clones the neuron description.
		 * \return The clone.
		 */
		AbstractCloneable* clone() const override;
		/**
		 * \brief Returns the input function of the neuron.
		 * \return The input function.
		 */
		const AbstractInputFunction& getInputFunction() const;
		/**
		 * \brief Returns the activation function of the neuron.
		 * \return The activation function.
		 */
		virtual const AbstractActivationFunction& getActivationFunction() const;
	};
}

#include "IO/NeuronDescriptionIO.hpp"

#endif