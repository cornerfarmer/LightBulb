#pragma once

#ifndef _SAMENEURONDESCRIPTIONFACTORYIO_H_
#define _SAMENEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "IO/NeuronDescriptionIO.hpp"
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory)
{
	archive(cereal::make_nvp("neuronDescription", descriptionFactory.neuronDescription));
}

namespace cereal
{
	template <> struct LoadAndConstruct<SameNeuronDescriptionFactory>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<SameNeuronDescriptionFactory>& construct)
		{
			std::unique_ptr<NeuronDescription> neuronDescription;
			ar(cereal::make_nvp("neuronDescription", neuronDescription));
			construct(neuronDescription.release());
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(SameNeuronDescriptionFactory);

#endif
