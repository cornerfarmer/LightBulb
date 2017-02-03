#pragma once

#ifndef _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_
#define _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a DifferentNeuronDescriptionFactory.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param descriptionFactory The DifferentNeuronDescriptionFactory to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, DifferentNeuronDescriptionFactory& descriptionFactory);
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::DifferentNeuronDescriptionFactory>
	{
		/**
		* \brief Constructs a DifferentNeuronDescriptionFactory.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The DifferentNeuronDescriptionFactory construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::DifferentNeuronDescriptionFactory>& construct);
	};
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(DifferentNeuronDescriptionFactory)

#endif
