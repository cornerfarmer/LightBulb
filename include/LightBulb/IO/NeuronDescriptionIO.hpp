#pragma once

#ifndef _NEURONDESCRIPTIONIO_H_
#define _NEURONDESCRIPTIONIO_H_

// Includes
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "cereal/access.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a NeuronDescription.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuronDescription The NeuronDescription to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, NeuronDescription& neuronDescription);
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::NeuronDescription>
	{
		/**
		* \brief Constructs a NeuronDescription.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The NeuronDescription construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::NeuronDescription>& construct);
	};
}

#endif
