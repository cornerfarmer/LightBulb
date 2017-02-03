#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORYIO_H_
#define _SAMENEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a SameNeuronDescriptionFactory.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param descriptionFactory The SameNeuronDescriptionFactory to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory);
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::SameNeuronDescriptionFactory>
	{
		/**
		* \brief Constructs a SameNeuronDescriptionFactory.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The SameNeuronDescriptionFactory construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::SameNeuronDescriptionFactory>& construct);
	};
}

#endif
