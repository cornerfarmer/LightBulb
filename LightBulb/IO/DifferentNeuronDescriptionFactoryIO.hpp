#pragma once

#ifndef _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_
#define _DIFFERENTNEURONDESCRIPTIONFACTORYIO_H_

// Libary includes
#include "IO/NeuronDescriptionIO.hpp"
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void serialize(Archive& archive, DifferentNeuronDescriptionFactory& descriptionFactory)
{
	archive(CEREAL_NVP(descriptionFactory.innerNeuronDescription));
	archive(CEREAL_NVP(descriptionFactory.outputNeuronDescription));
}

namespace cereal
{
	template <> struct LoadAndConstruct<DifferentNeuronDescriptionFactory>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<DifferentNeuronDescriptionFactory>& construct)
		{
			std::unique_ptr<NeuronDescription> innerNeuronDescription;
			ar(innerNeuronDescription);
			std::unique_ptr<NeuronDescription> outputNeuronDescription;
			ar(outputNeuronDescription);
			construct(innerNeuronDescription.release(), outputNeuronDescription.release());
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(DifferentNeuronDescriptionFactory);

#endif
