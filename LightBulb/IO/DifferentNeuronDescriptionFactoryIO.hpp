#pragma once

#ifndef _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_
#define _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
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
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LightBulb::DifferentNeuronDescriptionFactory>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<NeuronDescription> innerNeuronDescription;
			ar(cereal::make_nvp("innerNeuronDescription", innerNeuronDescription));
			std::unique_ptr<NeuronDescription> outputNeuronDescription;
			ar(cereal::make_nvp("outputNeuronDescription", outputNeuronDescription));

			construct(innerNeuronDescription.release(), outputNeuronDescription.release());
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DifferentNeuronDescriptionFactory);

#endif
