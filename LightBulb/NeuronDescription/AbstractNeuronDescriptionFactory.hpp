#pragma once

#ifndef _ABSTRACTNEURONDESCRIPTIONFACTORY_H_
#define _ABSTRACTNEURONDESCRIPTIONFACTORY_H_

namespace LightBulb
{
	// Forward declarations
	class NeuronDescription;
	class AbstractActivationFunction;

	/**
	 * \brief Describes a factory which provides neurons descriptions depending on the layer.
	 */
	class AbstractNeuronDescriptionFactory
	{
	private:
	public:
		virtual ~AbstractNeuronDescriptionFactory() {}
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
		virtual const AbstractActivationFunction* getOutputActivationFunction() const = 0;
		/**
		* \brief Returns the activation function for inner/hidden neurons.
		* \return The activation function.
		*/
		virtual const AbstractActivationFunction* getInnerActivationFunction() const = 0;
		/**
		* \brief Clones the neuron description factory.
		* \return The clone.
		*/
		virtual AbstractNeuronDescriptionFactory* getCopy() const = 0;
	};
}

#endif