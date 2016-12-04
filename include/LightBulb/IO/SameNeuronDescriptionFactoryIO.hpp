#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORYIO_H_
#define _SAMENEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a SameNeuronDescriptionFactory.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param descriptionFactory The SameNeuronDescriptionFactory to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory)
	{
		archive(cereal::make_nvp("neuronDescription", descriptionFactory.neuronDescription));
	}
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
		static void load_and_construct(Archive & ar, construct<LightBulb::SameNeuronDescriptionFactory>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<NeuronDescription> neuronDescription;
			ar(make_nvp("neuronDescription", neuronDescription));
			construct(neuronDescription.release());
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::SameNeuronDescriptionFactory);

#endif
