#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORY_H_
#define _SAMENEURONDESCRIPTIONFACTORY_H_

// Library Includes
#include <memory>

// Includes
#include "NeuronDescription/AbstractNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	// Forward declarations

	/**
	* \brief Describes a neuron description factory which provides the same neuron descriptions for all neurons.
	*/
	class SameNeuronDescriptionFactory : public AbstractNeuronDescriptionFactory
	{
		template <class Archive>
		friend void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory);
	private:
		/**
		 * \brief Contains the neuron description for all neurons.
		 */
		std::unique_ptr<NeuronDescription> neuronDescription;
	public:
		/**
		 * \brief Creates a new SameNeuronDescriptionFactory.
		 * \param neuronDescription_ The neuron description for all neurons.
		 */
		SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_);
		/**
		 * \brief Copy constructor.
		 * \param obj A SameNeuronDescriptionFactory which should be copied.
		 */
		SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory &obj);
		// Inherited:
		NeuronDescription* createInnerNeuronDescription() override;
		NeuronDescription* createOutputNeuronDescription() override;
		AbstractNeuronDescriptionFactory* getCopy() const override;
		const AbstractActivationFunction* getOutputActivationFunction() const override;
		const AbstractActivationFunction* getInnerActivationFunction() const override;
	};
}

#include "IO/SameNeuronDescriptionFactoryIO.hpp"

#endif