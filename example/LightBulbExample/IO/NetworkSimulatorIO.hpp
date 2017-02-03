#pragma once

#ifndef _NETWORKSIMULATORIO_H_
#define _NETWORKSIMULATORIO_H_

// Includes
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

template <class Archive>
extern void save(Archive& archive, NetworkSimulator const& environment);

template <class Archive>
extern void load(Archive& archive, NetworkSimulator& environment);

namespace cereal
{
	CONSTRUCT_EXISTING(NetworkSimulator, LightBulb::AbstractEvolutionEnvironment)
	{
		template <class Archive>
		static void construct(Archive& ar, NetworkSimulator& environment);
	};
}

#endif