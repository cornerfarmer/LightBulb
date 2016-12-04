#pragma once

#ifndef _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_
#define _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a DifferentNeuronDescriptionFactory.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param descriptionFactory The DifferentNeuronDescriptionFactory to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, DifferentNeuronDescriptionFactory& descriptionFactory)
	{
		archive(cereal::make_nvp("innerNeuronDescription", descriptionFactory.innerNeuronDescription));
		archive(cereal::make_nvp("outputNeuronDescription", descriptionFactory.outputNeuronDescription));
	}
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
		static void load_and_construct(Archive & ar, construct<LightBulb::DifferentNeuronDescriptionFactory>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<NeuronDescription> innerNeuronDescription;
			ar(make_nvp("innerNeuronDescription", innerNeuronDescription));
			std::unique_ptr<NeuronDescription> outputNeuronDescription;
			ar(make_nvp("outputNeuronDescription", outputNeuronDescription));

			construct(innerNeuronDescription.release(), outputNeuronDescription.release());
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DifferentNeuronDescriptionFactory);

#endif
