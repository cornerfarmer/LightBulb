#pragma once

#ifndef _DIFFERENTFUNCTIONSNEURONFACTORY_H_
#define _DIFFERENTFUNCTIONSNEURONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronDescription/AbstractNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a neuron description factory which provides different neuron descriptions for inner and output neurons.
	 */
	class DifferentNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
	{
		template <class Archive>
		friend void serialize(Archive& archive, DifferentNeuronDescriptionFactory& descriptionFactory);
	private:
		/**
		* \brief Contains the neuron description for inner neurons.
		*/
		std::unique_ptr<NeuronDescription> innerNeuronDescription;
		/**
		 * \brief Contains the neuron description for output neurons.
		 */
		std::unique_ptr<NeuronDescription> outputNeuronDescription;
	public:
		/**
		 * \brief Creates a new DifferentNeuronDescriptionFactory.
		 * \param innerNeuronDescription_ The neuron description for inner neurons.
		 * \param outputNeuronDescription_ The neuron description for output neurons.
		 */
		DifferentNeuronDescriptionFactory(NeuronDescription* innerNeuronDescription_, NeuronDescription* outputNeuronDescription_);
		/**
		 * \brief Copy constructor.
		 * \param obj A DifferentNeuronDescriptionFactory which should be copied.
		 */
		DifferentNeuronDescriptionFactory(const DifferentNeuronDescriptionFactory &obj);
		// Inherited:
		NeuronDescription* createInnerNeuronDescription() override;
		NeuronDescription* createOutputNeuronDescription() override;
		AbstractCloneable* clone() const override;
		const AbstractActivationFunction& getOutputActivationFunction() const override;
		const AbstractActivationFunction& getInnerActivationFunction() const override;
	};
}

#include "IO/DifferentNeuronDescriptionFactoryIO.hpp"

#endif