#pragma once

#ifndef _NETWORKSIMULATORIO_H_
#define _NETWORKSIMULATORIO_H_

// Includes
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, NetworkSimulator const& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
	archive(cereal::make_nvp("consumers", world.consumers));
}

template <class Archive>
void load(Archive& archive, NetworkSimulator& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
	archive(cereal::make_nvp("consumers", world.consumers));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(NetworkSimulator);

#endif