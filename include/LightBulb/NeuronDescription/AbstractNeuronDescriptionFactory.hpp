#pragma once

#ifndef _ABSTRACTNEURONDESCRIPTIONFACTORY_H_
#define _ABSTRACTNEURONDESCRIPTIONFACTORY_H_

// Includes
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include <utility>

namespace LightBulb
{
	// Forward declarations
	class NeuronDescription;
	class AbstractActivationFunction;
	class AbstractInputFunction;

	/**
	 * \brief Describes a factory which provides neurons descriptions depending on the layer.
	 */
	class AbstractNeuronDescriptionFactory : public virtual AbstractCloneable, public virtual AbstractLinearAlgebraUser
	{
	private:
	public:
		virtual ~AbstractNeuronDescriptionFactory() {}
		friend void swap(AbstractNeuronDescriptionFactory& lhs, AbstractNeuronDescriptionFactory& rhs) noexcept	{}
		/**
		 * \brief Creates a new neuron description for inner/hidden neurons.
		 * \return The new neuron description.
		 */
		virtual NeuronDescription* createInnerNeuronDescription() = 0;
		/**
		* \brief Creates a new neuron description for output neurons.
		* \return The new neuron description.
		*/
		virtual NeuronDescription* createOutputNeuronDescription() = 0;
		/**
		* \brief Returns the activation function for output neurons.
		* \return The activation function.
		*/
		virtual const AbstractActivationFunction& getOutputActivationFunction() const = 0;
		/**
		* \brief Returns the activation function for inner/hidden neurons.
		* \return The activation function.
		*/
		virtual const AbstractActivationFunction& getInnerActivationFunction() const = 0;
		/**
		* \brief Returns the input function for output neurons.
		* \return The activation function.
		*/
		virtual const AbstractInputFunction& getOutputInputFunction() const = 0;
		/**
		* \brief Returns the input function for inner/hidden neurons.
		* \return The activation function.
		*/
		virtual const AbstractInputFunction& getInnerInputFunction() const = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractNeuronDescriptionFactory, LightBulb)

#endif