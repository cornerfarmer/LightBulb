#pragma once

#ifndef _NETWORKSIMULATORIO_H_
#define _NETWORKSIMULATORIO_H_

// Includes
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, NetworkSimulator const& environment)
{
	archive(cereal::base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
	archive(cereal::make_nvp("consumers", environment.consumers));
}

template <class Archive>
void load(Archive& archive, NetworkSimulator& environment)
{
	archive(cereal::base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
	archive(cereal::make_nvp("consumers", environment.consumers));
}

namespace cereal
{
	CONSTRUCT_EXISTING(NetworkSimulator, LightBulb::AbstractEvolutionEnvironment)
	{
		template <class Archive>
		static void construct(Archive& ar, NetworkSimulator& environment)
		{
			ar(base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
			ar(make_nvp("consumers", environment.consumers));
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(NetworkSimulator);

#endif